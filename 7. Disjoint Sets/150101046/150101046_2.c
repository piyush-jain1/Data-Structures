/* 
Name - PIYUSH JAIN
Roll No. - 150101046
*/

/* 
Assignment 7, Question 2 : 
This program takes objects as input , makes set of each of them.
It repeatedly gives their current set representative or joins two disjoint sets as per the wish of the user.
Uses Union by Rank and Path Compression
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

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
     int rank ;             // rank of set
};

// function to create an object
struct obj * create_obj(int x,struct obj * parent[])
{
    struct obj * temp=(struct obj *)malloc(sizeof(struct obj));

    temp->val=x ;
    temp->rep=temp;
    temp->next=NULL;
    parent[x]=temp->rep;

    return temp;
}

// function to make a set of each object
void MAKE_SET (int x,struct set * setlist,struct obj * parent[])
{
    struct obj * temp=create_obj(x,parent);

    (setlist+x)->head=(setlist+x)->tail=temp;
    (setlist+x)->rank=0;
}

// recursive function for FIND_SET with path compression, returns the representative of an object x
struct obj * FIND_SET(int x,struct obj * parent[])
{
    if(x!=parent[x]->val)
    {
        parent[x]=FIND_SET(parent[x]->val,parent);
    }
    return (parent[x]);
}

// function to join set containing object x and set containing object y, joining the set with lower rank to the set with higher rank
void UNION(int x, int y,struct set * setlist,struct obj * parent[])
{   
    // if rank of set containing x is greater than rank of set containing y
    if((setlist+parent[x]->val)->rank > (setlist+parent[y]->val)->rank)
    {
        // join representative set containing y to representative of set containing x
        parent[parent[y]->val]=parent[parent[x]->val];
    }

    else
    {
        struct obj * temp = parent[x];

        // join representative set containing x to representative of set containing y
        parent[parent[x]->val]=parent[parent[y]->val];

        // if the ranks are equal
        if((setlist+temp->val)->rank==(setlist+parent[y]->val)->rank)
        {   
            // increase rank of final set by 1
            (setlist+parent[y]->val)->rank+=1;
        }
    }
}

// utility function to find the final head of each element
int findrep(int x,struct obj * parent[])
{   
    int temp = x;

    // while object is not representative of itself
    while(parent[temp]->val != temp)
    {
        temp = parent[temp]->val;
    }
    return temp;
}

// utility function to check the validity of input
int belong(int x,int a[],int k)
{
    int i;

    for(i=0;i<k;i++)
    {
        if(x==a[i])
        {
            return 0;
        }
    }
    return 1;
}

// utility function to print all disjoint sets
void print_set(struct obj * parent[],int a[],int k)
{
    int i;
    int set_array[k][k];
    int j=0;
    int t[k];

    // initialization
    for(i=0;i<k;i++)
    {
        for(j=0;j<k;j++)
        {
            set_array[i][j]=0;
        }
    }

    // group elements on the basis of their representative and store it in array
    for(i=0;i<k;i++)
    {
        t[i]=0;
        for(j=0;j<k;j++)
        {
            if(findrep(a[j],parent)==a[i])
            {
                set_array[i][t[i]]=a[j];
                t[i]+=1;
            }
        }
    }

    // print final array
    int count=0;
    for(i=0;i<k;i++)
    {
        if(set_array[i][0]!=0)
        {
            printf("SET %d : [ ",++count);
        }

        for(j=0;j<k;j++)
        {
            if(set_array[i][j]!=0)
            {
                printf("%d ",set_array[i][j]);
            }
        }

        if(set_array[i][0]!=0)
        {
            printf("]\n");
        }
    }
}

// main function
int main()
{
    int k , i ;

    // get the number of objects to be inserted
    printf("Enter no of values : ");
    scanf("%d",&k);

    // array to store pointer to representative of each object
    struct obj * parent[MAX_SIZE];
    // array of sets
    struct set * setlist = (struct set *)malloc(MAX_SIZE*sizeof(struct set));

    int a[k];
    printf("Enter %d values : \n",k);

    // take k objects as input and make set of each object
    for(i=0;i<k;i++)
    {
        scanf("%d",&a[i]);

        MAKE_SET(a[i],setlist,parent);
    }

    // print all disjoint sets initially
    printf("Initially : \n");
    print_set(parent,a,k);

    int wish=0;
    // define menu of operations
    printf("\nMENU of operations : \n\n");
    printf("1. For FIND_SET  - Press 1\n");
    printf("2. For UNION   -    Press 2\n");
    printf("3. For Exit - Press 3\n\n");

    int x=0,y=0;

    // perform according to wish value repeatedly until exit command
    while(1)
    {
        printf("Your Wish : ");

        scanf("%d",&wish);

        // FIND_SET operation
        if(wish==1)
        {   
            // ask for input x until it is valid
            do{
                printf("Enter a value to get its representative : ");
                scanf("%d",&x);
                }while(belong(x,a,k)==1);

            // print the set representative of the set containing x
            printf("Set Representative of '%d' : '%d'\n",x,FIND_SET(x,parent)->val);
        }

        // UNION operation
        else if(wish==2)
        {   
            // ask for inputs x and y until they are valid
            do{
                printf("Enter two values to get the union of sets containing them : ");
                scanf("%d %d",&x,&y);
                }while(belong(x,a,k)==1 || (belong(y,a,k))==1);

            // join the set containing object x and set containing object y
            UNION(x,y,setlist,parent);

            // print all disjoint sets
            printf("%d , %d \n",findrep(x,parent),findrep(y,parent));

            print_set(parent,a,k);
        }

        // EXIT
        else if(wish==3)
        {
            printf("Exiting the program\n");
            exit(0);
        }

        else
        {
            printf("Invalid input\n");
        }
    }

    return 0;
}
