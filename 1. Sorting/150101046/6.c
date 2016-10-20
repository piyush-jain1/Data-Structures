/*
Name  - PIYUSH JAIN
Roll No. - 150101046
*/
#include <stdio.h>
#include <stdlib.h>
//merging the two subarrays
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

//merge sort
void mergesort(int *a,int l ,int r)
{
        if(l<r)
        {
                int m=l+(r-l)/2;
                mergesort(a,l,m);
                mergesort(a,m+1,r);
                merge(a,l,m,r);
        }
}
//find whether a and b exists or not
int find(int a[],int p,int n)
{
    int l=0,r=n-1,mid;
    mid=l+(r-l)/2;
    //checks for p in array a[]
    while(a[mid]!=p)
    {

        if(l>=r)
        {
            return 0;
        }
        if(a[mid]<p)
        {
            l=mid+1;
        }
        else
        {
            r=mid-1;
        }
        mid=l+(r-l)/2;
    }
    return 1;
}

int main()
{
    int n,m,flag;
    // input no. of elements
    printf(("n="));
    scanf("%d",&n);
    // input desired sum
    printf(("m="));
    scanf("%d",&m);
    int a[n],b[n];
    int i,j;
    // generating n random numbers for both arrays
    for(i=0;i<n;i++)
    {
        a[i]=rand()%10;
        b[i]=rand()%10;
    }
    for(j=0;j<n;j++)
    {
        printf("%d  %d\n",a[j],b[j]);
    }
    mergesort(a,0,n-1);

    int p;
    // result
    for(i=0;i<n;i++)
    {   p=m-b[i];
        flag=find(a,p,n);
        if(flag==1)
        {
            printf("a and b exist.\na=%d   b=%d",p,m-p);    //Values of a and b
            break;

        }

    }
    if(flag==0)
    {printf("Don't exist.\n");}

    return 0;
}



