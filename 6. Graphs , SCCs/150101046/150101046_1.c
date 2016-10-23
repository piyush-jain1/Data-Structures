#include <stdio.h>
#include <stdlib.h>

struct node {
    int nodeid ;
    struct node * next ;
    char col ;
    int d ;
    int f ;
} ;

struct edgelist {
    char x;
    char y;
} ;

struct root {
    int id ;
    struct root * ptr;
};
struct root * head = NULL ;

int time = 0 ; 



void create_adj( struct node * adj , struct edgelist * edge , int n , int e )
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

void DFS_Visit ( struct node * adj , int i , int n )
{    
    int j;
    int k=0;
    struct node* temp = (adj+i) ;
    printf("%d-->", (adj+i)->nodeid );
    temp->col='g' ;
    time=time+1;
    temp->d=time ;
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
    time=time+1;
    (adj+i)->f=time;
    struct root * dummy = (struct root *)malloc(sizeof(struct root)) ;
    dummy->id = (adj+i)->nodeid;
    
    dummy->ptr=head;
    head=dummy;
    
    

} 
void DFS_Visit2 ( struct node * adj , int i , int n )
{    
    int j;
    int k=0;
    struct node* temp = (adj+i) ;
    
    temp->col='g' ;
    time=time+1;
    temp->d=time ;
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
            printf("%d  ",(adj+j)->nodeid);    
            DFS_Visit2(adj,j,n);    
        }
    }
    (adj+i)->col='b';
    time=time+1;
    (adj+i)->f=time;
    struct root * dummy = (struct root *)malloc(sizeof(struct root)) ;
    dummy->id = (adj+i)->nodeid;
    
    dummy->ptr=head;
    head=dummy;
    
    

} 



void DFS1 ( struct node * adj ,int n )
{
    int i ;
    for (i = 0 ; i < n ; i++ )
    {
        if ( (adj+i)->col == 'w' ) 
        {
            DFS_Visit(adj,i,n);
        }
    }
    printf("||\n") ;
}

void DFS2 ( struct node * adj ,int n )
{
    int i ,j;
    int count = 1;
    struct root * dum ;
    dum=head ;

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
            printf("SCC %d : %d  ",count,(adj+i)->nodeid);
            count++;
            DFS_Visit2(adj,i,n);
            printf("\n");
        }
    
        dum=dum->ptr;
        
    }
    
}


void SCC ( struct node * adj , struct node * tradj, int n )
{
    DFS1 (adj,n) ;
    
    DFS2 (tradj,n) ;



}

int main()
{
    int n , e ;
    scanf ( "%d %d" , &n , &e ) ;

    struct node * adj = (struct node * ) malloc ( n * sizeof( struct node ) ) ;
    struct node * tradj = (struct node * ) malloc ( n * sizeof( struct node ) ) ;
    int i , j ;

    //initialize the adjacency list of input graph and Transpose of graph
    for ( i = 0 ; i < n ; i++ )
    {
        (adj+i)->nodeid = i+1 ;
        (tradj+i)->nodeid = i+1 ;
        (adj+i)->next = NULL ;
        (tradj+i)->next = NULL ;
        (adj+i)->col = 'w' ;
        (tradj+i)->col = 'w' ;
        (adj+i)->d = 0 ;
        (tradj+i)->d = 0 ;
        (adj+i)->f = 0 ; 
        (tradj+i)->f = 0 ; 
    }

    struct edgelist * edge = (struct edgelist * ) malloc ( e * sizeof( struct edgelist )) ;
    int n1 , n2 ;

    //scan edges
    for ( i = 0 ; i < e ; i++ )
    {
        scanf("%d %d", &n1 , &n2 ) ;
        (edge+i)->x = n1 ;
        (edge+i)->y = n2 ;
    }

    printf("\nOriginal Graph : \n");
    create_adj (adj,edge,n,e) ;
    printGraph (adj,n) ;


    printf("\nTranspose Graph : \n");
    transpose (tradj,edge,n,e) ;
    printGraph (tradj,n) ; 

    
    printf("DFS : ");
    DFS1 (adj,n) ;
    

    create_adj (adj,edge,n,e) ;  

    SCC(adj,tradj,n);







 }