/*PIYUSH JAIN
Roll No. - 150101046 */
#include <stdio.h>
#include <stdlib.h>

// Finding Span O(n^2)
int * span(int *x,int n)
{
    int i,j;
    int * count=(int *)malloc(n*sizeof(int));

    for(i=0;i<n;i++)
    {   count[i]=0;     //initialization of count
        for(j=i;j>=0;j--)
        {
            if(x[j]<=x[i])
            {
                count[i]++;
            }
            else
            {
                break;
            }
        }


    }

    return count;   //returns array
}



// Push Function
int* push(int* a,int top,int x)
{

    a[++top]=x;
    return a;

}

// Finding Span using stack O(n)
int * span_using_stack(int* a,int top,int *x, int n)
{
    int i;
    int * count=(int *)malloc(n*sizeof(int));
    count[0]=1; // count will always be 1 for index 0
    a=push(a,top,0);    // Push 0 as first element in stack
    top+=1;
    // Calculate span for rest of the elements
    for(i=1;i<n;i++)
    {
        //Pop elements while stack is not empty and until first bigger number is found
        while(top!=-1 && x[a[top]]<=x[i])
        {
            top-=1;     //pop
        }
        // if stack is empty then current element is bigger than all elements left to it
        if(top==-1)
        {
            count[i]=i+1;
        }
        // else current element is bigger than the elements upto the index stored in top of stack
        else
        {
            count[i]=i-a[top];
        }
        // push current element to stack
        push(a,top,i);
        top+=1;
    }
    return count;   //returns array

}
int main()
{
    int i,n;
    printf("Give no. of elements : ");      // User enters number of elements
    scanf("%d",&n);
    int* x;     // array X
    int *s,*t;
    // Declaring arrays for X and output S using pointers
    x=(int *)malloc(n*sizeof(int));
    s=(int *)malloc(n*sizeof(int));
    t=(int *)malloc(n*sizeof(int));
    printf("Enter %d numbers : ",n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&x[i]);       // taking input in array X from user
    }
    printf("X : ");
    for(i=0;i<n;i++)
    {
        printf("%d  ",*(x+i));      //print array X
    }
    printf("\n");
    s=span(x,n);    // array S using O(n^2) algorithm
    printf("S : ");
    for(i=0;i<n;i++)
    {
        printf("%d  ",*(s+i));      //print array S
    }

    int a[1000];    // Declaration of array for stack
    int top=-1;     // Initialization of top (empty stack)

    printf("\n");
    t=span_using_stack(a,top,x,n);       // array S using Stack:O(n) algorithm
    printf("S(using Stack) : ");
    for(i=0;i<n;i++)
    {
        printf("%d  ",*(t+i));      //print array S
    }
    return 0;
}
