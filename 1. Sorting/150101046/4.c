/*
Name  - PIYUSH JAIN
Roll No. - 150101046
*/
#include <stdio.h>
#include <stdlib.h>
// Merge two subarrays
void merge(int a[],int l,int m,int r)
{
    int n1=m-l+1;
    int n2=r-m;
    int L[n1],R[n2];
    int i,j;
    for(i=0;i<n1;i++)
    {
        L[i]=a[l+i];
    }
    for(j=0;j<n2;j++)
    {
        R[j]=a[m+1+j];
    }
    i=j=0;
    int k=l;
    while(i<n1 && j<n2)
    {
        if(L[i]<=R[j])
        {
            a[k++]=L[i++];
        }
        else
        {
            a[k++]=R[j++];
        }
    }
    while(i<n1)
    {
        a[k++]=L[i++];
    }
    while(j<n2)
    {
        a[k++]=R[j++];
    }

}
// merge sort through recursive calls
void mergesort(int a[],int l,int r)
{
    if(l<r)
    {
        int m=l+(r-l)/2;
        mergesort(a,l,m);
        mergesort(a,m+1,r);
        merge(a,l,m,r);
    }
}


int main()
{

    int n,i;
    printf("n=");
    scanf("%d",&n);
    int a[1000];
    //generate n random numbers
    for(i=0;i<n;i++)
    {
        a[i]=rand()%1000;
    }

    mergesort(a,0,n-1);        //call merge sort

    printf("Sorted Array : \n");
    //print the final sorted array
    for(i=0;i<n;i++)
    {
        printf("%d\n",a[i]);
    }

    return 0;
}

