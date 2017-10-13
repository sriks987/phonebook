//phonebook code


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20

typedef struct node node;

struct node
{
 node *a[27];                                      // array of 27 pointers 1 for space and 26 for the letters
 float *data;                                      // data is the phone number
};

struct book
{
 node *root;                                       // structure for the phone book
};
typedef struct book book;

void menu();                                        // menu to choose from various actions
void create_book(book *ph);                         // to create a new phone book
void create_node(node *temp);                      // to create a new node in the tree
void create_num(float *temp,float num);            // to insert the phone number after the location has been found
void insert(float num,char *name,book *ph);          // to insert a new phone number given the name and the person's number
void search(char *name, book*ph);                           // to search for the number given the name of the person
void initialize(book *ph, char *file);
         // to initialize the tree
void main()
{
 menu();
}

void menu()
{
 int r; char file[SIZE];
 printf("Welcome to the phone book\n");
 book phone;
 create_book(&phone);
 char decision,name[SIZE];
 float num;
 do
 {
   if (r==2)
       printf("\n\n1. Search for a number\n2. Provide phonebook data through file\n3. Provide new record\n4. Exit\n\n");
   r=0;
   scanf("%c",&decision);
   switch(decision)
   {
     case '1':search(name, &phone);
              r=2;
              printf("Enter the name: ");
              scanf("%s",name);
              break;
     case '2':printf("Enter the filename: ");
              scanf("%s",file);
              initialize(&phone, file);
              r=2;
              break;
     case '3':printf("Enter the person's name: ");
              scanf("%s",name);
              name[SIZE]= toUpper(name);
              printf("Enter the number: ");
              scanf("%s",&num);
              insert(num,name,&phone);
              r=2;
              break;
     case '4':r=1;
              break;
   }
  }while(r==0 || r==2);
}


void create_book(book *ph)
{
 create_node(ph->root);
}

void create_node(node *temp)
{
 temp->data = NULL;
 int i;
 for(i=0;i<27;i++)
  temp->a[i]=NULL;
}

void create_num(float *temp,float num)
{
 temp = (float*)malloc(sizeof(float));
 *temp = num;
}

void insert(float num,char *name,book *ph)
{
 node *temp = ph->root;
 int i;
 for(i=0;name[i]!='\0';i++)
 {
   if (name[i]!=32)
   {
      if(temp->a[name[i]%65]==NULL)
        create_node(temp->a[name[i]%65]);
      temp = temp->a[name[i]%65];
   }
   else if(name[i]==32)
   {
      if(temp->a[26]==NULL)
        create_node(temp->a[26]);
      temp = temp->a[26];
   }
   else
   {
     printf("Name cannot have any special characters.\n");
     return;
   }
 }
 create_num(temp->data,num);
}

void search(char *name, book* ph)
{
 node *temp = ph->root;
 int i;
 for(i=0;name[i]!='\0';i++)
 {
  if (name[i]!=32)
  {
    if (temp->a[name[i]%65]==NULL)
    {
        printf("Number does not exist");
        return;
    }
    else
        temp = temp->a[name[i]%65];
  }
  else if (name[i]==32)
  {
    if (temp->a[26]==NULL)
    {
        printf("Number does not exist");
        return;
    }
    else
        temp = temp->a[26];
  }
  else
  {
    printf("Number does not exist");
    return;
  }
 }
 printf("The number is : %f",*(temp->data));
}

void initialize(book *ph, char *file)
{
 FILE *fptr;
 if ((fptr=fopen(file,"r")) == NULL)
 {
    fprintf (stderr, "can't open %s\n", file);
    exit (-1);
 }
 char name[SIZE],num[SIZE],buffer[50];
 while(feof(fptr)==0)
 {
   int i=0;
   if (fgets(buffer,128,fptr) == NULL)            //breaks out of the loop if the file ends
       break;
   name[SIZE]= toUpper(name);
   name[SIZE] = strtok(buffer,",");
   num[SIZE] = strtok(NULL,",");
   insert(atof(num),name,ph);
 }
}


