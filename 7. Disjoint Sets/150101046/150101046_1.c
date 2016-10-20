/* 
Name - PIYUSH JAIN
Roll No. - 150101046
*/

/* 
Assignment 7, Question 1 : 
This program takes objects as input , makes set of each of them.
It repeatedly gives their current set representative or joins two disjoint sets as per the wish of the user.
Uses Weighted Union Heuristic
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
     int size ;             // number of objects in the set
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
    (setlist+x)->size=1;
}

// returns the representative of an object
int FIND_SET(int x,struct obj * parent[])
{
    return parent[x]->val;
}

// function to join sets containing object x and set containing object y following weighted union heuristic
void UNION(int x, int y,struct set * setlist,struct obj * parent[])
{
    // if the two objects are already in the same set
    if(FIND_SET(x,parent)==FIND_SET(y,parent))
    {
        return;
    }

    // if size of set containing x is greater than size of set containing y , swap x and y
    int tempval;
    if((setlist+parent[x]->val)->size >(setlist+parent[y]->val)->size)
    {
        tempval=x;
        x=y;
        y=tempval;

    }

    // join set x at the end of set containing y
    (setlist+parent[y]->val)->tail->next=parent[x];
    (setlist+parent[y]->val)->tail=(setlist+parent[x]->val)->tail;
    struct obj * temp = parent[x];

    // update represenatative of all the objects of set containing x as the representative of y and increase the set size
    while(temp!=NULL)
    {
        temp->rep= parent[y] ;
        parent[temp->val]=parent[y];
        (setlist+parent[y]->val)->size+=1;
        temp=temp->next;
    }
}

// utility function to print each disjoint set
void print_set(struct obj * parent[],int a[],int k)
{
    int i,set_no=0;
    for(i=0;i<k;i++)
    {   
        // if value of object is same as its set representative
        if(a[i]==parent[a[i]]->val)
        {
            printf("SET %d : ",++set_no);
            struct obj * temp=parent[a[i]];
            printf("[ ");
            while(temp!=NULL)
            {
                printf("%d ",temp->val);
                temp=temp->next;
            }
            printf("]\n");
        }
    }
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


// main function
int main()
{
    int k , i ;

    // get the number of objects to be inserted
    printf("Enter no of objects : ");
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
    printf("3. For EXIT - Press 3\n\n");

    int x=0,y=0;

    // perform according to wish value repeatedly until exit command
    while(1)
    {
        printf("\nYour Wish : ");
        scanf("%d",&wish);

        // FIND_SET operation
        if(wish==1)
        {   
            // ask for input x until it is valid
            do{
                printf("Enter a value to get its representative : ",k);
                scanf("%d",&x);
                }while(belong(x,a,k)==1);

            // print the set representative of the set containing x
            printf("Set Representative of '%d' : '%d'\n",x,FIND_SET(x,parent));
        }

        // UNION operation
        else if(wish==2)
        {   
            // ask for inputs x and y until they are valid
            do{
                printf("Enter two values to get the union of sets containing them : ",k);
                scanf("%d %d",&x,&y);
                }while(belong(x,a,k)==1 || (belong(y,a,k))==1);

            // join the set containing object x and set containing object y
            UNION(x,y,setlist,parent);

            // print all disjoint sets
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
