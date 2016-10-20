/*
Name - Piyush Jain
Roll No. - 150101046
*/


/*
This program finds the Minimum Spanning Tree of a given undirected graph stored as adjacency matrix.
It will take time in O(V^2).
*/

#include <stdio.h>
#include <stdlib.h>

// define maximum value of key , must be greater than any possible weight
#define MAX_KEY 100         

// function to find the vertex with minimum key

int find_min(int MST_Vertex[],int key[],int n)
{
    int i;

    // initialize min
    int min = MAX_KEY;

    // initilaize min_vertex
    int min_vertex=0;

    // loop running over all the vertices to get the vertex with minimum key value
    for(i=1;i<n+1;i++)
    {
        if( MST_Vertex[i]==0 && key[i]<min )
        {
            min=key[i];
            min_vertex=i;
        }
    }

    // return the vertex with minimum key value
    return min_vertex;

}

// main function

int main()
{
    int n,e,v;
    
    int n1,n2,w;

    // scan number of vertices and number of edges
    scanf ( "%d %d" , &n , &e ) ;

    int i,j;

    // declare and initialize adjacency matrix to store the graph
    int a[n+1][n+1];
    for(i=0;i<n+1;i++)
    {
        a[i][0]=i;
        a[0][i]=i;
    }

    for(i=1;i<n+1;i++)
    {
        for(j=1;j<n+1;j++)
        {
            a[i][j]=0;
        }
    }

    // scan edges and weights and assign to the adjacency matrix
    for(i=0;i<e;i++)
    {
        scanf("%d %d %d",&n1,&n2,&w);
        a[n1][n2]=w;
        a[n2][n1]=w;
    }
    
    // array to store key values
    int key[n+1];

    // array to store value of previous vertex
    int pi[n+1];

    // set key and pi of first vertex to 0
    key[1]=0;
    pi[1]=0;

    // set keys of rest of the vertices to be maximum
    for(i=2;i<n+1;i++)
    {
        key[i]=MAX_KEY ;
    }

    // array to store whether the vertex has been inserted into the MST or not. It will take values either 1(inserted) or 0(not inserted)
    int MST_Vertex[n+1];

    // initialization
    for(i=0;i<n+1;i++)
    {
        MST_Vertex[i]=0;
    }

    
    // This loop will run n-1 times, each time finding the correct edge to be inserted in the MST
    for(j=1;j<n;j++)
    {   
        // find the vertex with minimum key
        v=find_min(MST_Vertex,key,n);

        // set its MST_Vertex value equal to 1, since it will noe be added into the MST
        MST_Vertex[v]=1;

        // This loop will update the key and pi values of all the adjacent vertices of v , if it has not yet been inserted into the MST
        for(i=1;i<n+1;i++)
        {
            if(a[v][i]!=0 && MST_Vertex[i]==0 && a[v][i]<key[i])
            {
                key[i]=a[v][i];
                pi[i]=v;
            }
        }
    }

    // print the edges and corresponding edge weights which are in the final MST
    printf("MST using Prim's Algorithm : \n");
    for(i=2;i<n+1;i++)
    {   
        printf("%d--%d of edge weight %d\n",pi[i],i,a[pi[i]][i]);
    }

    return 0;

}

