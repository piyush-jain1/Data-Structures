#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int nodeid ;
    struct node * next ;
    char col ;
} ;

struct edgelist
{
    int x ;
    int y ;
} ;

void DFS_Visit(struct node* adj,int n)
{
    int j;
    struct node * temp=adj;
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
            printf("%d ", (adj+j)->nodeid);    
            DFS_Visit(adj+j,n);    
        }
    }
}

void DFS(struct node* a, int n)
{
    int i,count=0;
    for(i=0;i<n;i++)
        if((a+i)->col=='w')
        {
            count++;
            printf("Component %d: %d ",count,(a+i)->nodeid);
            DFS_Visit(a+i,n);
            printf("\n");
        }
}

int main()
{   
    const char ch ='r';
    const char*p;
    p=&ch;
    FILE *fp;
    int n,e;
    fp=fopen("input.txt",p);
    fscanf(fp,"%d %d",&n,&e);
    
    //scanf ( "%d %d" , &n , &e ) ;
    int i , j ;
    struct node * adj = (struct node * )malloc( n*sizeof( struct node ) ) ;
    for ( i = 0 ; i < n ; i++ )
    {
        (adj+i) -> nodeid = i+1 ;
        (adj+i) -> next = NULL ;
        (adj+i) -> col = 'w';
    }
    struct edgelist * edge = ( struct edgelist * )malloc( e*sizeof( struct edgelist ) ) ;
    int n1,n2;
    for( i = 0 ; i < e ; i++ )
    {    
        fscanf( fp,"%d %d" , &n1 , &n2 ) ;
        (edge+i) -> x = n1;
        (edge+i) -> y = n2;
        for(j=1;j<=n;j++)
        {    if ( (edge[i]).x == j )
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
    
    DFS(adj,n);

}


