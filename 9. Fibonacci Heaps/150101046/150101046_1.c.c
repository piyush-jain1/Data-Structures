#include <stdio.h>
#include <stdlib.h>

struct node {
int key;
int degree;
struct node * parent;
struct node * child;
struct node * left;
struct node * right;
int mark;
} ;


struct node * INSERT ( struct node * min , int k )
{
struct node * new = (struct node *)malloc(sizeof(struct node));

new -> key = k;
new -> degree = 0;
new -> parent = NULL;
new -> child = NULL;
new -> left = new;
new -> right = new;
new -> mark = 0;

if( min == NULL )
{
min = new;
}

else
{
struct node * temp ;
temp = min->right ;
min ->right = new ;
new ->right = temp;
temp ->left = new ;
new -> left = min ;


if ( new->key < min->key )
{
min = new;
}
}

return min ;
}

struct node * CREATE ( struct node * min )
{
int size;
printf("Enter Size : ");
scanf("%d",&size);
int i;
for ( i = 0 ; i < size ; i++ )
{
min = INSERT ( min , rand()%100 );
}
return min ;
}

struct node * CONCAT ( struct node * min1 , struct node * min2 )
{

if ( min1 != NULL && min2 != NULL )
{
struct node * temp1;
struct node * temp2;
temp1 = min1 -> right ;
min1 -> right = min2 ;
temp2 = min2 -> left ;
temp2 -> right = temp1 ;
temp1 -> left = temp2 ;
min2 -> left = min1 ;
if( min2 -> key < min1 -> key )
{
return min2 ;
}
return min1 ;
}
else if ( min1 != NULL )
{
return min1;
}
else if ( min2 != NULL )
{
return min2;
}

}

void Print ( struct node * min )
{
if ( min!=NULL )
{
printf("Circular Doubly Linked List : \n");
struct node * temp = min;
do
{
printf("[%d , %d ", temp->key , temp ->degree );
if(temp->mark==0)
{
printf(", FALSE ]\n");
}
else
{
printf("TRUE ]\n");
}
temp = temp->right;
}while(temp!=min);

printf("\n");
}

}

// utility function to count the number of nodes
int numberOfNodes ( struct node * min )
{
int count = 0 ;
if ( min!=NULL )
{
struct node * temp = min;
do
{
count++;
temp = temp->right;
}while(temp!=min);
}
return count ;
}

// utility function to make min2 as child of min1
struct node * CREATE_CHILD ( struct node * min1 , struct node * min2 )
{

if ( min1!=NULL && min2!=NULL )
{
min1 -> degree += numberOfNodes ( min2 );
struct node * temp = min2;
do
{
temp -> parent = min1;
temp = temp->right ;
}while(temp!=min2);

if(min1 -> child == NULL )
{
min1 -> child = min2;
}

else
{
min1->child=CONCAT ( min1->child , min2 ) ;
}


}

return min1;

}

struct node * HEAP_LINK ( struct node * min , struct node * y , struct node * x )
{
if( min != NULL )
{

// if node to be removed is minimum
if ( min == y )
{
struct node * find = min ;
do
{
int minimum = 1000000;
if( find->key <  minimum && find!=min )
{
minimum = find->key;
min = find;
}
find = find -> right ;
}while(find!=x);
}

struct node * temp = y;
y -> right -> left = temp -> left ;
y -> left -> right = temp -> right ;
y -> left = y ;
y -> right = y ;
y -> mark = 0 ;
min = CREATE_CHILD ( x , y ) ;




}
return min ;  
}

int main()
{
printf("-----------------ASSIGNMENT 9------------------- \n");
struct node * min1 = NULL;
struct node * min2 = NULL;

min1 = CREATE (min1) ;
min2 = CREATE (min2) ;

printf("No. of Nodes in the Linked List1 = %d\n",numberOfNodes(min1) );
Print( min1 );
printf("No. of Nodes in the Linked List2 = %d\n",numberOfNodes(min2) );
Print( min2 );

struct node * new;
new = CONCAT ( min1 , min2 ) ;
printf("No. of Nodes in the New Linked List = %d\n",numberOfNodes(new) );
Print( new ) ;

struct node * a = NULL;
struct node * b = NULL;
struct node * c = NULL;
a = CREATE (a) ;
Print ( a ) ;
b = CREATE (b) ;
Print ( b ) ;
c = CREATE_CHILD ( a ,b ) ;
Print (c) ;

a = HEAP_LINK ( a , a , a->right ) ;
Print ( a ) ;



return 0;

}