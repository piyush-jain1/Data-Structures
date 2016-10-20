/*
Name - PIYUSH JAIN
Roll No. - 150101046
*/

#include <stdio.h>
#include <stdlib.h>


// Enqueue function
int * enqueue(int q[],int rear, int x)
{
    q[++rear]=x;
    return q;

}
// Dequeue function
int dequeue(int q[],int front,int rear)
{
    // check if empty
    if(front==-1 && rear==-1)
    {
        return front;
    }
    front+=1;
    return front;
}



int main()
{
    //Declaring no of processes and arrays for arrival time and execution time
    int n=6;
    int a[n],b[n],exec[n];

    // Taking data for all the processes
    a[0]=0; exec[0]=250;
    a[1]=50; exec[1]=170;
    a[2]=130; exec[2]=75;
    a[3]=190; exec[3]=100;
    a[4]=210; exec[4]=130;
    a[5]=350; exec[5]=50;

    // Crating an instance of execution time in another array
    int i,j;
    for(i=0;i<n;i++)
    {
        b[i]=exec[i];
    }

    int time_quantum,remain=n,k=1;

    // Creating queue using array
    int * q=(int *)malloc(100*sizeof(int));
    int curr=0,start=0;
    int front=-1,rear=-1;
    int out[n][1000];       //array for storing output
    int index[1000]={0};    //array for indexing output array

    // taking time quantum from user
    printf("Enter time quantum : ");
    scanf("%d",&time_quantum);

    i=0;

    while(remain!=0)

    {
        // Enqueue all processes whose arrival time fall in the current time slot
        while(a[i]>=(k-1)*time_quantum && a[i]<=k*time_quantum && b[i]!=0)
        {
            q=enqueue(q,rear,i);
            if(front==-1 && rear ==-1)
            {
                front+=1;
            }
            rear+=1;
            i++;
        }


        curr=q[front];      //store front element as curr
        out[curr][index[curr]++]=start;     //setting start time for current process

        front=dequeue(q,front,rear);    // dequeue process at the end of time slot
        if(b[curr]>time_quantum)
        {
            // enqueue current process again at the end if it is not completed
            q=enqueue(q,rear,curr);
            rear+=1;
            out[curr][index[curr]++]=start+time_quantum;    // setting end time for current process
            start=start+time_quantum;   // storing start time for next process in queue
            b[curr]-=time_quantum;  //  updating the time left for exhaustion of current process

        }
        else
        {
            out[curr][index[curr]++]=start+b[curr];     // setting end time for current process
            start=start+b[curr];    // storing start time for next process in queue
            b[curr]=0;  // current process terminated, time left for exhaustion is zero
            remain--;   //decreasing remain variable as one process has ended
        }


        k++;    // updating round number

    }

    // Prints the output for Process[0]
    printf("Process[0]  : ");
    printf("<%d - %d> ",out[0][0],out[0][1]);
    for(j=2;;j+=2)
    {
        if(out[0][j]!=0)
        {
            printf("<%d - %d> ",out[0][j],out[0][j+1]);
        }
        else
            break;

    }
    printf("\n");
    // prints the output for rest of the processes
    for(i=1;i<n;i++)
    {
        printf("Process[%d]  : ",i);
        for(j=0;;j+=2)
        {
            if(out[i][j]!=0)
            {
                printf("<%d - %d> ",out[i][j],out[i][j+1]);
            }
            else
                break;
        }
        printf("\n");
    }
}














