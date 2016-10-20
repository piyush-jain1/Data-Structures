/*
Name  - PIYUSH JAIN
Roll No. - 150101046
*/
#include <stdio.h>
#include <stdlib.h>

#define MERGE_SORT_THRESHOLD 55

// for binary insertion, finding the position after which element has to be inserted
int binary_pos(int a[],int l,int r,int key)
{
    int m=l+(r-l)/2;
    if(r-l==-1)
    {
        return r;
    }
    if(a[m]>=key)
    {
        return binary_pos(a,l,m-1,key);
    }
    else
    {
        return binary_pos(a,m+1,r,key);
    }
}

// function for sorting through binary insertion
void binary_insertion(int a[],int l,int r)
{
    int i,j;
    for(i=l+1;i<=r;i++)
    {   
        int key=a[i];
        int pos=binary_pos(a,l,i-1,a[i]);
        for(j=i-1;j>pos;j--)
        {
            a[j+1]=a[j];    // shifting elements
        }
        a[pos+1]=key;
    }
    

}

//    merging two half subarrays
void merge(int a[],int l,int r,int m)
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
    R[j]=a[m+j+1];
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

//sorting : using binary insertion after a threshold, and then merging subarrays
void sorting(int a[],int l,int r)
{
   if(l<r)
   { if((r-l+1)<MERGE_SORT_THRESHOLD)
    {
    binary_insertion(a,l,r);    // use binary insertion sort when no. of elements has reduced to less than threshold
    }
    
    int m=l+(r-l)/2;
    sorting(a,l,m);
    sorting(a,m+1,r);
    merge(a,l,r,m);    // finally merge
  }
}
        
        
        

int main()
{
    
    int j;
    int n=100;
    double time[100];
   
    int i;
    
    int a[1000];
    // generating n random  numbers and printing unsorted array
    printf("Unsorted array : \n");
    for(i=0;i<n;i++)
    {
        a[i]=rand()%1000;
        printf("%d  ",a[i]);
    }
    printf("\n");
    
    sorting(a,0,n-1);
    
    printf("Sorted Array : \n");
    // printing the final sorted array
    for(i=0;i<n;i++)
    {
    printf("%d\n",a[i]);
    }
   
    

    
    return 0;
}

