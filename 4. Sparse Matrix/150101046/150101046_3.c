/*
Name - Piyush Jain
Roll No. - 150101046
*/

/* This program generates a sparse matrix with random entries at random coordinates and also gives the maximum values of those elements */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100


struct rooted {                         // struct type for root node
    struct rheader* firstrow ;
    struct cheader* firstcol ;
    int noofrows ;
    int noofcols ;
} ;

struct element{                         // struct type for element node
    struct element* down ;
    struct element* right ;
    int row ;
    int col ;
    int val ;
} ;

struct cheader {                        // struct type column header
    struct cheader* right ;
    struct element* down ;
    int index ;
} ;


struct rheader {                        // struct type row header
    struct element* right ;
    struct rheader* down ;
    int index ;
} ;

struct sparse {                         // struct type for overall structure of sparse matrix
    struct rooted* root ;               // stores root node
    struct cheader *chead[MAX] ;        // stores column header 
    struct rheader *rhead[MAX] ;        // stores row header
    struct element* elem ;              // stores element node
} ;

struct point {                          // struct type for insertion point coordinates
    int r ;
    int c ;
} ;
struct point pos[1000] ;

struct maxm {                           // struct type for storing maximum value and its coordinates
    int val;
    int rowno;
    int colno;
};

// function to initialize structure elements for the sparse matrix

void initialize_sparse ( struct sparse *s , int row , int col )
{
    int i ;

    // create row headnodes 
    for ( i = 0 ; i < row ; i++ )
        s -> rhead[i] = ( struct rheader * ) malloc ( sizeof ( struct rheader ) ) ;

    // initialize and link row headnodes together 
    for ( i = 0 ; i < row - 1 ; i++ )
    {
        s -> rhead[i] -> down = s -> rhead[i + 1] ;
        s -> rhead[i] -> right = NULL ;
        s -> rhead[i] -> index = i ;
    }
    s -> rhead[i] -> right = NULL ;
    s -> rhead[i] -> down = NULL ;

    // create col headnodes 
    for ( i = 0 ; i < col ; i++ )
        s -> chead[i] = ( struct cheader * ) malloc ( sizeof ( struct cheader ) ) ;

    // initialize and link col headnodes together
    for ( i = 0 ; i < col-1 ; i++ )
    {
        s -> chead[i] -> right = s -> chead[i + 1] ;
        s -> chead[i] -> down = NULL ;
        s -> chead[i] -> index = i ;
    }
    s -> chead[i] -> down = NULL ;
    s -> chead[i] -> right = NULL ;

    // create and initialize root node
    s -> root = ( struct rooted * ) malloc ( sizeof ( struct rooted ) ) ;
    s -> root -> firstcol = s -> chead[0] ;
    s -> root -> firstrow = s -> rhead[0] ;
    s -> root -> noofcols = col ;
    s -> root -> noofrows = row ;
}


// function to insert element into the sparse matrix

void insert ( struct sparse *p,int r, int c, int v )
{
    struct element *temp1, *temp2 ;
    struct rheader *rh ;
    struct cheader *ch ;
    int i,j ;

    // allocate and initialize memory for the element node to be inserted

    p -> elem = ( struct element * ) malloc ( sizeof ( struct element ) ) ;
    p -> elem -> col = c ;
    p -> elem -> row = r ;
    p -> elem -> val = v ;

    // get the first row headnode 

    rh = p ->root ->firstrow ;

    // move to the desired row headnode 
    for ( i = 0 ; i < r ; i++ )
    {
        rh = rh->down ;
    }

    // move to the first element node of the row

    temp1 = rh -> right ;


    // if no element added in the row

    if ( temp1 == NULL )
    {
        rh -> right = p -> elem ;
        p -> elem -> right = NULL ;
    }

    // if first element node is after the column for the new node

    else if(temp1 -> col > c)
    {
        p -> elem -> right = temp1 ;       
        rh -> right = p -> elem ;
    }

    else
    {
        temp2 = temp1 ;

        // add element at proper position

        while ( ( temp1 != NULL  ) && ( temp1 -> col < c ) )
        {

            temp2 = temp1 ;
            temp1 = temp1 -> right ;
        }

        p -> elem -> right = temp2 -> right ;
        temp2 -> right = p -> elem ;
    }



    // get the first column headnode

    ch = p -> root -> firstcol ;

    // move to the desired column headnode

    for ( j = 0 ; j < c ; j++ )
    {
        ch = ch->right;
    }

    // move to the first element node of the column

    temp1 =ch -> down ;



    // if no element added in the column

    if ( temp1 == NULL )
    {
        ch -> down =p -> elem ;
        p -> elem -> down = NULL ;

    }

    // if first element node is after the row for the new node

    else if(temp1 -> row >r)
    {
        p -> elem -> down = temp1 ;
        ch -> down = p -> elem ;
    }

    else
    {
        temp2=temp1;

        // add elemet at proper position

        while ( ( temp1 != NULL ) && ( temp1 -> row < r ) )
        {

            temp2 = temp1 ;
            temp1 = temp1 -> down ;

        }

        p->elem->down=temp2->down;
        temp2->down= p -> elem ;


    }

    printf("%d\n",v);
}




// function to find unique random coordinates for inserting new nodes

void unique_randompos ( int r , int c , int elements )
{

    int random_r,random_c ;
    int uniqueflag ;
    int i,j ;

    for( i=0 ; i < elements ; i++ )
    {
        uniqueflag = 1 ;                    // set uniqueflag = 1
        random_r = rand() % r ;             // generate random values for row number
        random_c = rand() % c ;             // generate random values for column number

        // check if the newly generated coordinate is already present

        for( j = 0 ; j < i ; j++ )
        {
            if ( (pos[j]).r == random_r && (pos[j]).c == random_c ) {
                uniqueflag = 0 ;
                i-- ;
                break ;
            }
        }

        // if the newly generated coordinate is unique

        if( uniqueflag == 1 )
        {
            (pos[i]).r = random_r ;
            (pos[i]).c = random_c ;
        }

    }
}


// function to find maximum value of element from the sparse matrix

struct maxm * findMax(struct sparse *s)
{
    struct cheader* tempc ;
    struct element* elem ;

    // get to the first column

    tempc = s -> root -> firstcol ;

    // creating a maxm type struct to store value and coordinates of element with maximum value

    struct maxm * m = (struct maxm *)malloc(sizeof(struct maxm)) ;
    m -> val = 0 ;           // initialize maximum value to zero
    
    // transverse until the last column

    while( tempc!=NULL )  
    {
        // move to the first element of the current column

        elem = tempc -> down ;

        // transverse down the elements column wise

        while( (elem)!=NULL )
        {   
            // if value of element is greater then current maximum , update maximum

            if( (elem->val) > (m->val) )
            {
                m -> val = elem -> val ;
                m -> rowno = elem -> row ;
                m -> colno = elem -> col ;
            }
            elem = elem -> down ;

        }
        tempc = tempc -> right ;

    }
    return m;
}



int main()
{
    int row , col , elements ;

    // take inputs for no of rows , no of columns , and no of non-zero elements
    printf ("Enter No of rows : ");
    scanf ( "%d" , &row );
    printf ("Enter No of columns : ");
    scanf ( "%d" , &col );
    printf ("Enter no of non- zero elements : ");
    scanf ( "%d" , &elements );
    printf ( "\n" );

    int i;

    struct sparse s1;
    struct sparse *s=&s1;

    // initialize structure of sparse matrix

    initialize_sparse (s,row,col);

    // generate unique random coordinates

    unique_randompos (row,col,elements);

    // insert random elements in sparse matrix

    for( i = 0 ; i < elements ; i++ )
    {
        printf ("Element  inserted at (%d.%d)  :   ", (pos[i]).r , (pos[i]).c ) ;

        insert (s,(pos[i]).r,(pos[i]).c,rand()%100);
    }


    struct maxm * m=(struct maxm *)malloc( sizeof ( struct maxm));

    // find maximum value and its coordinates

    m = findMax ( s );

    // printing the maximum value

    printf ("\nMaximum value is %d which is stored at (%d,%d)\n", m->val , m->rowno , m->colno ) ;

    return 0;
}
