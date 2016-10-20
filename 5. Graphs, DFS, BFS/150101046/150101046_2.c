/* 
Name - Piyush Jain
Roll  No. - 150101046
*/

#include <stdio.h>
#include <stdlib.h>

/*
This program finds if there is any path between two nodes.
Output is printed in the form of an array. 
If out[i][j]=1 , it means there is a path between node 'i' and node 'j'.
If out[i][j]=0 , it means there is no path between node 'i' and node 'j'.
*/

// declare struct for nodes of adjacency list
struct node
{
    int nodeid ;
    struct node * next ;
    char col ;
} ;

// declare struct to store edgelist
struct edgelist
{
    int x ;
    int y ;
} ;

// function to visit in depth-first order for each node, and simultaneouly update the pathnode array

void DFS_Visit(struct node* adj,int curr,int n,int pathnode[][n],int k,int t)
{
    int j;
    struct node * temp=(adj+curr);
    temp->col ='g';
    while ( (temp->next)!=NULL )
    {

        temp=temp->next;

        for ( j = 0 ; j < n ; j ++ )
        {
            if( temp -> nodeid == (adj+j) -> nodeid )
            {
                break;
            }
        }

        if( (adj+j) -> col == 'w' )
        {
            pathnode[k][t]=(adj+j)->nodeid;     // pathnode array get the nodeid which is connected to parent node of DFS_Visit
            DFS_Visit(adj,j,n,pathnode,k,t+1);
        }
    }
}

// function to perform depth-first search 

void DFS(struct node* adj, int n,int pathnode[][n])
{
    int i,j,t=1;
    for(i=0;i<n;i++)
    {   

        // make all the nodes white before visiting any node to get all the nodes which are connected to i'th node

        for(j=0;j<n;j++)
        {
            (adj+j)->col='w';
        }

        pathnode[i][0]=(adj+i)->nodeid;     // pathnode stores the index for which DFS_Visit is going to run

        DFS_Visit(adj,i,n,pathnode,i,t);

    }


}


int main()
{
    int n,e;

    scanf("%d %d",&n,&e);


    int i , j ;
    // initialize all the nodes
    struct node * adj = (struct node * )malloc( n*sizeof( struct node ) ) ;

    for ( i = 0 ; i < n ; i++ )
    {
        (adj+i) -> nodeid = i+1 ;
        (adj+i) -> next = NULL ;
        (adj+i) -> col = 'w';
    }

    struct edgelist * edge = ( struct edgelist * )malloc( e*sizeof( struct edgelist ) ) ;

    int n1,n2;

    // take input of edges and simultaneously build adjacency list

    for( i = 0 ; i < e ; i++ )
    {
        scanf( "%d %d" , &n1 , &n2 ) ;

        (edge+i) -> x = n1;
        (edge+i) -> y = n2;

        // build adjacency list

        for(j=1;j<=n;j++)
        {    
            if ( (edge[i]).x == j )
            {
                struct node * temp = ( struct node * )malloc( sizeof( struct node ) ) ;
                temp -> nodeid = (edge[i]).y ;
                temp -> next = (adj+j-1) -> next ;
                temp -> col = 'w' ;
                (adj+j-1)->next = temp ;

            }

            if ( (edge[i]).y == j )
            {
                struct node * temp = ( struct node * )malloc( sizeof( struct node ) ) ;
                temp -> nodeid = (edge[i]).x ;
                temp -> next = (adj+j-1) -> next ;
                temp -> col = 'w' ;
                (adj+j-1) ->next = temp ;
            }


        }

    }

    int pathnode[n][n];     // array which stores all connections with a node

    int out[n+1][n+1];      // final output array showing 0's and 1's

    // initialize pathnode array

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            pathnode[i][j]=0;

        }
    }

    // initialize output array

    for(i=0;i<n+1;i++)
    {
        out[i][0]=i;
        out[0][i]=i;
    }

    for(i=1;i<n+1;i++)
    {
        for(j=1;j<n+1;j++)
        {
            out[i][j]=0;

        }
    }

    // depth-first search on graph

    DFS(adj,n,pathnode);


    // update the values of output array according to the information of paths from the pathnode array

    for(i=0;i<n;i++)
    {
        for(j=1;j<n;j++)
        {
            if(pathnode[i][j]!=0)
            {
                out[pathnode[i][0]][pathnode[i][j]]=1;
            }

        }

    }

    printf("Output Matrix : \n\n");


    for(i=0;i<n+1;i++)
    {

        for(j=0;j<n+1;j++)
        {

            printf("%d ",out[i][j]);
        }
        printf("\n");
    }



}


