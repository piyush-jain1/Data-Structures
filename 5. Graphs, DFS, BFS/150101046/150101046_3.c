/* 
Name - Piyush Jain
Roll  No. - 150101046
*/

/* 
This programs takes a graph as input , builds its adjacency list. 
It finds the values of d[v] and f[v] for each node.
Then it assigns the edge connecting them on the basis of values of d[v] and f[v].
*/

#include <stdio.h>
#include <stdlib.h>

// declare struct for nodes of adjacency list
struct node{
    int nodeid;
    struct node* next;
    char col;
    int d;
    int f;
    int pi;
};

// declare struct to store edgelist
struct edgelist{
    int x;
    int y;
};

int time = 0;

// function to visit in depth-first order of each node, thus updating d[v] and f[v] values

void DFS_Visit(struct node * a, int n)
{
    int j;
    struct node * temp = a;
    a->col = 'g';
    time=time+1;
    a->d = time;

    while ( (temp-> next)!= NULL )
    {
        temp=temp->next;

        for(j=0;j<n;j++)
        {
            if(temp->nodeid == (a+j)->nodeid)
            {
                break;
            }
        }

        if((a+j) -> col == 'w' )
        {
            (a+j) -> pi = a->nodeid;

            DFS_Visit(a+j,n);
        }
    }

    a->col='b';

    time = time+1;

    a->f=time;
}

// function to perform depth first search on graph

void DFS(struct node * adj, int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        if((adj+i)->col=='w')
        {
            DFS_Visit(adj+i,n);
        }
    }
}


int main()
{
    int n , e , i ,j ,k;

    // read input for no of nodes and no of edges

    scanf ( "%d %d" , &n , &e ) ;

    int n1,n2;

    // initialize nodes

    struct node * adj = (struct node * ) malloc(n*sizeof(struct node));

    for(i=0 ; i<n ; i++)
    {
        (adj+i) -> nodeid = i+1;
        (adj+i) -> next = NULL;
        (adj+i) -> col = 'w';
        (adj+i) -> d = 0;
        (adj+i) -> f = 0;
        (adj+i) -> pi = 0;
    }

    // create edgelist

    struct edgelist * edge = (struct edgelist * )malloc(e*sizeof(struct edgelist));

    // take input of edges and simultaneously build adjacency list

    for(i=0;i<e;i++)
    {
        scanf("%d %d",&n1,&n2);

        (edge+i)-> x = n1;
        (edge+i)-> y = n2;

        // build adjacency list

        for(j=0;j<n;j++)
        {
            if(n1==j)
            {
                struct node * temp = (struct node *)malloc(sizeof(struct node));
                temp->nodeid = n2;
                temp->next = (adj+j-1)->next;
                temp->col='w';
                (adj+j-1)->next=temp;
            }
            if(n2==j)
            {
                struct node * temp = (struct node *)malloc(sizeof(struct node));
                temp->nodeid = n1;
                temp->next = (adj+j-1)->next;
                temp->col='w';
                (adj+j-1)->next=temp;
            }
        }
    }

    // run DFS on graph

    DFS(adj,n);
    
    // checking conditions for each edge and thus printing its type

    for(k=0;k<e;k++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if((edge+k)->x == i+1 && (edge+k)->y == j+1)
                {
                    if((adj+j)->d < (adj+i)->d && (adj+i)->d < (adj+i)->f && (adj+i)->f < (adj+j)->f)
                    {
                        printf("(%d,%d) - Back Edge \n",(edge+k)->x,(edge+k)->y);
                    }
                    if((adj+j)->d < (adj+j)->f && (adj+j)->f < (adj+i)->d && (adj+i)->d < (adj+i)->f)
                    {
                        printf("(%d,%d) - Cross Edge \n",(edge+k)->x,(edge+k)->y);
                    }
                    if((adj+i)->d < (adj+j)->d && (adj+j)->d < (adj+j)->f && (adj+j)->f < (adj+i)->f && ((adj+j)->d)-((adj+i)->d)==1)
                    {
                        printf("(%d,%d) - Tree Edge \n",(edge+k)->x,(edge+k)->y);
                    }
                    if((adj+i)->d < (adj+j)->d && (adj+j)->d < (adj+j)->f && (adj+j)->f < (adj+i)->f && ((adj+j)->d)-((adj+i)->d)>1)
                    {
                        printf("(%d,%d) - Forward Edge \n",(edge+k)->x,(edge+k)->y);
                    }
                }
            }
        }
    }


    return 0;
}
