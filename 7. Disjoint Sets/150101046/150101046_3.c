/* 
Name - PIYUSH JAIN
Roll No. - 150101046
*/

/* 
Assignment 7, Question 3 :
This program takes a string as input.
String contains unique digits(0-9) or char 'E'.
When it finds an integer, it adds it to the set , and when it finds an 'E' , it calls EXTRACT-MIN and returns minimum of the existing set.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VALUE 1000

// struct for object of a set
struct obj {
    int val ;           // value stored in object
    struct obj * rep ;  // pointer to its set representative
    struct obj * next ; // pointer to its next object
};

// struct for set
struct set {
     struct obj * head ;    // pointer to head of set
     struct obj * tail ;    // pointer to tail of set
};

// function to create an object
struct obj * create_obj(int x)
{
    struct obj * temp=(struct obj *)malloc(sizeof(struct obj));

    temp->val=x ;
    temp->rep=temp;
    temp->next=NULL;

    return temp;
}

// function to make a set of each object
struct set * MAKE_SET (int x)
{
    struct obj * temp=create_obj(x);
    struct set * newset = (struct set *)malloc(sizeof(struct set));

    newset->head=newset->tail=temp;
    
    return newset;
}

// function to join set of new object to the existing set
void INSERT(int x,struct set * setlist)
{
    // create set of new object
    struct set * tempset = MAKE_SET(x);

    // if already existing set is empty
    if(setlist->head==NULL)
    {
        setlist->head=tempset->head;
        setlist->tail=tempset->tail;
    }

    else
    {
        (setlist)->tail->next=tempset->head;
        (setlist)->tail=tempset->tail;
    }


//  print_set(setlist);

}

/*
// utility function to print currently existing set
void print_set(struct set * setlist)
{

    struct obj * temp=setlist->head;
    while(temp!=NULL)
    {

        printf("%d--",temp->val);
        temp=temp->next;
    }
    printf("\n");
}
*/

// function to extract the minimum value from the currently existing set and remove it from the set
int EXTRACT_MIN(struct set * setlist)
{   
    // if set is not empty
    if(setlist->head!=NULL)
    {   
        // initialize min
        int min=MAX_VALUE;

        struct obj * temp = setlist->head;

        struct obj * prev = setlist->head;
        struct obj * curr = setlist->head;
    
        // check head of set
        if(temp->val<min)
        {
            min=temp->val;
        }

        // traverse rest of the set
        while(temp->next!=NULL)
        {      
            // update prev and curr when min is updated
            if(temp->next->val<min)
            {
                prev=temp;
                curr=prev->next;
                min=temp->next->val;
            }

            temp=temp->next;
        }

        // if min found is the first element of set
        if(prev==setlist->head && curr==setlist->head)
        {
            setlist->head=curr->next;
        //  print_set(setlist);
            return min;
        }

        // if min found is last element of the set
        if(curr==setlist->tail)
        {
            curr=prev->next=NULL;
            setlist->tail=prev;
        //  print_set(setlist);
            return min;
        }

        prev->next=curr->next;
    //  print_set(setlist);
        return min;

    }
}

// main function

int main()
{


    struct set * setlist = (struct set *)malloc(sizeof(struct set));
    setlist->head= NULL;
    setlist->tail=NULL;

    char input[1001];
    char a[2];
    char test[2]="E";
    int p[1000];
    int i=0;
    for(i=0;i<1000;i++)
    {
        p[i]=0;
    }

    // take the input string
    scanf("%1000[^\n]s",input);

    char query[1001];
    int j=0;
    int n=0,m=0;
    int len=strlen(input);
    i=0;
    // find n and m
    while(i<len)
    {
        if(input[i]!=',' && input[i]!=' ')
        {
            j++;
        }
        if(input[i]=='E')
        {
            m++;
        }
        i++;
    }
    n=j-m;
    j=0;
    i=0;
    int k=0;
    // puts -1 in array p if input is 'E' , puts the number if there is a number , else puts 0
    while(i<len)
    {
        if(input[i]!=',' && input[i]!=' ' && input[i]!='E')
        {
            query[j++]=input[i];
        }
        else
        {

            if(input[i]=='E')
            {
                p[k++]=-1;
            }
            else
            {   
                // conversion of data type of number from string to int
                p[k++]=(int)strtol(query,NULL,10);
            }
            strncpy(query, "", sizeof(query));
            j=0;

        }
        i++;
    }
    // size of array p
    int size=k;


    int extract[m];

    j=0;
    k=0;


    for(i=0;i<size;i++)
    {


        if(p[i]==-1)
        {
            extract[j++]=EXTRACT_MIN(setlist);
        }
        else if(p[i]!=0)
        {
            INSERT(p[i],setlist);
        }


    }

    // print the final extracted array
    printf("Extracted : ");
    for(i=0;i<m;i++)
    {
       printf("%d ",extract[i]);
    }



}