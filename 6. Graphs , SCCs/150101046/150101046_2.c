/*
Name - Piyush Jain
Roll No. - 150101046
*/

/* 
This program finds takes a directed graph as input , finds its SCCs and then computes its component graph ( i.e. graph of its SCCs ).
*/

#include <stdio.h>
#include <stdlib.h>


// struct for each node of adjacency list to represent the graph
struct node {
    int nodeid ;
    struct node * next ;
    char col ;
    int SCC_num;

} ;

// struct for edge
struct edgelist {
    char x;
    char y;
} ;

// struct for linked list which will store the node id's in decresing order of their finishing time
struct root {
    int id ;
    struct root * ptr;
};
struct root * head = NULL ;

// declaration of prototypes for DFS_Visit and DFS_Visit_tr functions
void DFS_Visit ( struct node * adj , int i , int n );
void DFS_Visit_tr ( struct node * adj , int i , int n , int ** SCC,int k);

// function to create adjacency list
void create_adj ( struct node * adj , struct edgelist * edge , int n , int e )
{
    int i , j ;
    for ( i = 0 ; i < e ; i++ )
    {
        for ( j = 1 ; j <= n ; j++ )
        {
            if ( (edge[i]).x == j )
            {
                struct node * temp = ( struct node * )malloc( sizeof( struct node ) ) ;
                temp -> nodeid = (edge[i]).y ;
                temp -> next = (adj+j-1) -> next ;
                temp -> col = 'w' ;
                (adj+j-1)->next = temp ;

            }
        }
    }
}

// function to create transpose graph of given graph and store it as adjacency list
void transpose ( struct node * tradj , struct edgelist * edge , int n , int e )
{
    int i , j ;
    for ( i = 0 ; i < e ; i++ )
    {
        for ( j = 1 ; j <= n ; j++ )
        {
            if ( (edge[i]).y == j )
            {
                struct node * temp = ( struct node * )malloc( sizeof( struct node ) ) ;
                temp -> nodeid = (edge[i]).x ;
                temp -> next = (tradj+j-1) -> next ;
                temp -> col = 'w' ;
                (tradj+j-1)->next = temp ;
            }
        }
    }
}

// function to print a graph stored as adjacency list
void printGraph ( struct node * adj , int n )
{
    int i ;
    for ( i = 0 ; i < n ; i++ )
    {
        struct node * temp = ( struct node * )malloc( sizeof( struct node ) ) ;
        temp = (adj+i);
        while (  temp != NULL )
        {
            printf("%d -- ", temp->nodeid );
            temp = temp->next ;
        }
        printf("\n");
    }
}


int count;

// function to perform Depth First Search in given graph
void DFS ( struct node * adj ,int n )
{
    int i ;
    for (i = 0 ; i < n ; i++ )
    {
        if ( (adj+i)->col == 'w' )
        {
            DFS_Visit(adj,i,n);
        }
    }
}

// recursive function to visit each node depth wise in DFS for given graph
void DFS_Visit ( struct node * adj , int i , int n )
{
    int j;

    struct node* temp = (adj+i) ;
    temp->col='g' ;

    while((temp->next)!=NULL)
    {
        temp=temp->next;
        for(j=0;j<n;j++)
        {
            if(temp->nodeid==j+1)
            {
                break;
            }
        }


        if( (adj+j) -> col == 'w' )
        {
            DFS_Visit(adj,j,n);
        }
    }
    
    (adj+i)->col='b';
    
    // adding finished nodeid at the start of the linked list
    struct root * dummy = (struct root *)malloc(sizeof(struct root)) ;
    dummy->id = (adj+i)->nodeid;
    dummy->ptr=head;
    head=dummy;
}

// function to perform Depth First Search in transpose graph
void DFS_tr ( struct node * adj ,int n , int ** SCC )
{
    int i ,j;
    count = 1;
    int k;

    struct root * dum ;
    dum=head ;

    // get the next node to visit according to the decreasing order of finishing time
    for(j=0;j<n;j++)
    {
        for(i=0;i<n;i++)
        {
            if((adj+i)->nodeid==dum->id)
            {
                break;
            }
        }


        if ( (adj+i)->col == 'w' )
        {
            // add the nodeid into the SCC array
            SCC[count-1][0]=(adj+i)->nodeid;

            // update the SCC number of current node
            ((adj+i)->SCC_num) = count ;

            k=1;

            DFS_Visit_tr(adj,i,n,SCC,k);
            count++;
        }

        dum=dum->ptr;

    }
}

// recursive function to visit each node depth wise in DFS of transpose graph
void DFS_Visit_tr ( struct node * adj , int i , int n , int ** SCC,int k)
{
    int j;

    struct node* temp = (adj+i) ;

    temp->col='g' ;
    
    while((temp->next)!=NULL)
    {
        temp=temp->next;
        for(j=0;j<n;j++)
        {
            if(temp->nodeid==j+1)
            {
                break;
            }
        }


        if( (adj+j) -> col == 'w' )
        {
            // add the nodeid into the current SCC array
            SCC[count-1][k]=(adj+j)->nodeid;

            // update the SCC number of the current node
            ((adj+j)->SCC_num) = count ;

            k++;

            DFS_Visit_tr(adj,j,n,SCC,k);

        }
    }

    (adj+i)->col='b';
}

// function to find all the SCCs in the given graph and store in a 2-D array SCC
void find_SCC ( struct node * adj , struct node * tradj, int n, int ** SCC )
{
    // perform DFS on given graph
    DFS (adj,n) ;

    // perform DFS on trapose graph in decreasing order of finishing time of DFS on original graph
    DFS_tr (tradj,n,SCC) ;
}

// function to compute the component graph ( i.e. graph of SCCs ) for the given directed graph and store it as adjacency matrix whose vertices are SCC numbers
void componentGraph(int ** SCC , int n , struct node * adj , struct node * tradj , int e, int ** SCCGraph )
{
    int i,j,k;

    struct node * temp;

    for(i=0;i<count-1;i++)
    {
        for(j=0;j<n;j++)
        {   
            // not a component of SCC
            if(SCC[i][j]==0)
            {
                break;
            }

            // visit the adjacency list of each element in SCC
            temp=(adj+SCC[i][j]-1);
            while((temp->next)!=NULL)
            {
                temp=temp->next;
                for(k=0;k<n;k++)
                {
                    if(temp->nodeid==k+1)
                    {
                        break;
                    }
                }

                // if the SCC number of the head node is not equal to the SCC number of the adjacent node, set an edge between the two SCC numbers in the component graph
                if((tradj+k)->SCC_num!=(tradj+SCC[i][j]-1)->SCC_num)
                {
                    SCCGraph[(tradj+SCC[i][j]-1)->SCC_num][(tradj+k)->SCC_num]=1;
                    break;
                }
            }
        }
    }
}


int main()
{
    int n , e ;
    scanf ( "%d %d" , &n , &e ) ;

    // input graph and transpose graph
    struct node * adj = (struct node * ) malloc ( n * sizeof( struct node ) ) ;
    struct node * tradj = (struct node * ) malloc ( n * sizeof( struct node ) ) ;
    int i , j ;

    //initialize the adjacency list of input graph and transpose graph
    for ( i = 0 ; i < n ; i++ )
    {
        (adj+i)->nodeid = i+1 ;
        (tradj+i)->nodeid = i+1 ;
        (adj+i)->next = NULL ;
        (tradj+i)->next = NULL ;
        (adj+i)->col = 'w' ;
        (tradj+i)->col = 'w' ;
        (adj+i)->SCC_num = 0;
        (tradj+i)->SCC_num = 0;
    }

    // edge list
    struct edgelist * edge = (struct edgelist * ) malloc ( e * sizeof( struct edgelist )) ;
    int n1 , n2 ;

    //scan edges
    for ( i = 0 ; i < e ; i++ )
    {
        scanf("%d %d", &n1 , &n2 ) ;
        (edge+i)->x = n1 ;
        (edge+i)->y = n2 ;
    }

    // create adjacency list of input graph
    create_adj (adj,edge,n,e) ;

    // print the input graph in the form of adjacency list
    printf("\nGiven Graph in the form of Adjacency List : \n");
    printGraph (adj,n) ;

    // create adjacency list for transpose graph
    transpose (tradj,edge,n,e) ;

    // 2-D array to store all the SCCs os the given graph
    int ** SCC;

    // initialization of array of SCCs
    SCC=(int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++)
    {
        SCC[i]=(int *)malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            SCC[i][j]=0;
        }
    }

    //find the SCCs ans store it in SCC array
    find_SCC(adj,tradj,n,SCC);

    // print the SCCs
    printf("\n");
    for(i=0;i<count-1;i++)
    {
        printf("SCC %d  : ", i+1);
        for(j=0;j<n;j++)
        {
            if(SCC[i][j]==0)
            {
                break;
            }
            printf("%d   ",SCC[i][j]);
        }
        printf("\n");
    }

    // adjacency matrix to store component graph ( i.e. graph of SCCs )
    int ** SCCGraph;

    // initialization of adjacency matrix of component graph
    SCCGraph=(int **)malloc(count*sizeof(int *));
    for(i=0;i<count;i++)
    {
        SCCGraph[i]=(int *)malloc(count*sizeof(int));
    }
    for(i=0;i<count;i++)
    {
        SCCGraph[i][0]=i;
        SCCGraph[0][i]=i;
    }
    for(i=1;i<count;i++)
    {
        for(j=1;j<count;j++)
        {
            SCCGraph[i][j]=0;
        }
    }
    // find the component graph and store it as adjacency matrix in SCCGraph
    componentGraph(SCC,n,adj,tradj,e,SCCGraph);

    // print the component graph
    printf("\nComponent graph in the form of Adjacency Matrix : \n");
    for(i=0;i<count;i++)
    {
        for(j=0;j<count;j++)
        {
            if(i>0 && j>0 && SCCGraph[i][j]==1 && SCCGraph[j][i]==1)
            {
                SCCGraph[j][i]=0;
            }
            printf("%d ",SCCGraph[i][j]);
        }
        printf("\n");
    }

    return 0;
}

