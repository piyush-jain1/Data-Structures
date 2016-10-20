/*
Name  - PIYUSH JAIN
Roll No. - 150101046
*/
#include <stdio.h>
#include <stdlib.h>


// count the no. of inversions while merging the subarrays
int merge(int a[],int l,int m,int r)
{
    static int inversion=0;
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
            inversion+=n1-i;    //whenever element in left subarray in greater than that in right subarray, inversion will increase by the no of elements remaining in the left subarray
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
    return inversion;
}
int mergesort(int a[], int l, int r)
{   int output;
    if(l<r)
    {
        int m=l+(r-l)/2;
        mergesort(a,l,m);
        mergesort(a,m+1,r);
        output=merge(a,l,m,r);
    }
    return output;

}

int main()
{
    int n,total;
    printf("n=");
    scanf("%d",&n);
    int* a=malloc(sizeof(int)*n);
    int i,out=0;
    for(i=0;i<n;i++)
    {
        scanf("%d",a+i);
    }


    total=mergesort(a,0,n-1);

    printf("%d\n",total);    //prints the total no. of inversions

    return 0;
}


