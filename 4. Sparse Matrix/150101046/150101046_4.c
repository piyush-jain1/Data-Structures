/*
Name - Piyush Jain
Roll No. - 150101046
*/

/* This program checks if there is a unique path between exactly two boundary points */

#include <stdio.h>
#include <stdlib.h>


struct coord {              // struct type for coordinates
    int x ;
    int y ;
} bound[2] , adjacent[4] ;

// function to count the no of adjacent 'L' ( mapped by 1 ) , it also stores their coordinates

int countadjacent( int row , int col , int a[row][col] , int i ,int j )
{
    int adj=0;              // initialization

    // checking all four adjacent nodes : up , down , left , right

    if(i+1<row)
        if(a[i+1][j]==1)
        {
            (adjacent[adj]).x=i+1;
            (adjacent[adj]).y=j;
            adj++;

        }
    if(i-1>=0)
        if(a[i-1][j]==1)
        {
            (adjacent[adj]).x=i-1;
            (adjacent[adj]).y=j;
            adj++;

        }
    if(j+1<col)
        if(a[i][j+1]==1)
        {
            (adjacent[adj]).x=i;
            (adjacent[adj]).y=j+1;
            adj++;
        }
    if(j-1>=0)
        if(a[i][j-1]==1)
        {
            (adjacent[adj]).x=i;
            (adjacent[adj]).y=j-1;
            adj++;
        }
    return adj;
}

// function to count the no of 'L' ( mapped by 1 ) at the boundary , it also stores their coordinates

int boundarycheck(int row,int col,int b[row][col])
{

    int i,j,count=0;

    int k=0;


    for(i=0;i<row;i++)
    {

        for(j=0;j<col;j++)
        {

            // if element is at boundary
            if(i==0 || i==row-1 || j==0 || j==col-1)
                {
                    // if element is 'L'
                    if(b[i][j]==1)

                    {
                        count++;

                        // store coordinates of boundary elements
                        if(k<2)
                            (bound[k]).x=i;
                            (bound[k]).y=j;
                            k++;

                    }
                }
        }
    }

    return count;

}

// function to check if there is a unique path from start coordinate to end coordinate

int pathcheck(int row,int col,int a[row][col])
{
    struct coord curr;
    struct coord prev;
    struct coord start;
    struct coord end;

    // starting coordinate is set as one of the two boundary coordinates

    start=bound[0];

    // ending coordinate

    end=bound[1];

    // if the boundary 'L' has no of adjacent 'L' not equal to 1

    if((countadjacent(row,col,a,start.x,start.y)!=1) || (countadjacent(row,col,a,end.x,end.y)!=1))
    {
        return -1;
    }

    int i;

    curr=start;

    countadjacent(row,col,a,curr.x,curr.y);
    prev=curr;
    curr=adjacent[0];



    while(1)
    {
        // if ending coordinate is reached

        if((curr.x)==end.x && (curr.y==end.y))
        {
            return 1;
        }

        // if current element has more than two adjacent 'L'

        if((countadjacent(row,col,a,curr.x,curr.y))!=2)
        {
            return -1;
        }

        // find the no of adjacent 'L' and also get their coordinates

        countadjacent(row,col,a,curr.x,curr.y);

        // if adjacent is not equal to prev , update prev to curr and curr to adjacent

        if((adjacent[0].x)==prev.x && (adjacent[0].y)==prev.y)
        {
            prev=curr;
            curr=adjacent[1];

        }
        else
        {
            prev=curr;
            curr=adjacent[0];
        }


    }

}
int main()
{
    int row,col;
    scanf("%d %d",&row,&col);
    int i,j;
    char a[row][col];
    int b[row][col];

    // taking input of row*col elements and mapping 1 for 'L' and 0 for 'T'

    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            scanf(" %c",&a[i][j]);
            if(a[i][j]=='L')
                b[i][j]=1;
            if(a[i][j]=='T')
                b[i][j]=0;
        }

    }

    // finding no of boundary elements and their coordinates

    boundarycheck(row,col,b);



    // if there are exactly two boundary points and both of them connected by a unique path

    if((pathcheck(row,col,b)==1) && (boundarycheck(row,col,b)==2))
    {
        printf("Submitted\n");
    }
    else
    {
        printf("Bad Luck !\n");
    }
    
    return 0;
}
