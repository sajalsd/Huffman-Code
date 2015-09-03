#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


struct list
{
    char c;
    int freq;
    struct list *left, *right, *next;
};

typedef struct list node;
node *temp2;
int count=0;
char str[256]={'\0'};
char character[100],codes[100];



node* insert(node *start, node* newnode);
void display(node *newnode);
node* huffman(node* start);
void codegen(node* root);





int main()
{
    int fr[256],i;
    char ch;
    FILE *fp;

    for(i=0; i<256; i++)
        fr[i]=0;

    fp = fopen("D:\\test.txt","r");

    if(fp==NULL)
       printf("\nError Opening File.\n");

    while(!feof(fp))
    {
        ch = fgetc(fp);
        printf("%c", ch);
        fr[ch]++;
    }
    printf("\n    Character          Frequency\n");

    for(i=0; i<256; i++)
    {
        if(fr[i]>0)
             printf("\t %c \t\t %d\n",i, fr[i]);
    }


    node *newnode, *start=NULL;

    for(i=0; i<256; i++)
    {
        if (fr[i]>0)
        {
            newnode = (node*)malloc(sizeof(node));
            newnode->c = i;
            newnode->freq = fr[i];
            newnode->left = NULL;
            newnode->right= NULL;
            newnode->next = NULL;
            start = insert(start,newnode);

        }
    }

    display(start);
    huffman(start);
    codegen(start);

    printf("THe codes are......:\n");
    for(i=0; i<10;i++)
    printf("%c   = d%\n", character[i], codes[i]);



    getch();
    return 0;

}

node* insert(node *start, node* newnode)
{
    node *temp, *temp1;


    if(start == NULL)
    {
         start = newnode;
         start->next = NULL;
    }
    else if(start->freq >= newnode->freq)
    {
         temp = (node*)malloc(sizeof(node));
         temp->freq = newnode->freq;
         temp->c = newnode->c;
         temp->next = start;
         start = temp;
    }
    else
    {
        temp = start;
        while((temp->next!=NULL)&&(temp->next->freq <= newnode->freq))
        {
            temp = temp->next;
        }
        temp1 = (node*)malloc(sizeof(node));
        temp1->freq = newnode->freq;
        temp1->c = newnode->c;
        temp1->next = temp->next;
        temp->next= temp1;
    }

    return start;

}


void display(node *newnode)
{
    node* temp;
    temp = newnode;

    printf("\n created list := ");
    printf("\n    Character          Frequency\n");

    while(temp != NULL)
    {
        printf("\t %c \t\t %d\n", temp->c, temp->freq);
        temp = temp->next;
    }
    return ;
}

node* deletion(node* start)
{
    node *temp;
    temp = start;
    start = start->next;
    temp2 = start;
    return temp;
}

node* huffman(node* start)
{
    node *x,*y,*z;
    while(start->next!=NULL)
    {
         x=deletion(start);
         start=temp2;
         y=deletion(start);
         start=temp2;
         z = (node*)malloc(sizeof(node));
         z->c = '*';
         z->freq = x->freq + y->freq;
         z->left = x;
         z->right = y;
         z->next = NULL;
         start = insert(start,z);

         printf("making tree.....\n");
         display(start);
         printf("\n");
    }
    return start;
}

void codegen(node* root)
{
    if(root!=NULL)
    {
         if(root->left!=NULL)
        {
           strcat(str,"0");
           codegen(root->left);
           str[strlen(str)-1]='\0';

        }

         if(root->right!=NULL)
        {
           strcat(str,"1");
           codegen(root->right);
           str[strlen(str)-1]='\0';
        }
         if(root->left==NULL&&root->right==NULL)
        {
           character[count] = root->c;
           strcpy(codes[count] = str);
           count++;
        }
    }
}

