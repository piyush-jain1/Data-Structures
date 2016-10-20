/*
Name - Piyush Jain
Roll No. - 150101046
*/

/* The problem is to find the lowest common ancestor of given two nodes in a binary tree.
 The algorithm which has been used is :
 Find the complete path of both the elements starting right from root.
 Store both the path in two arrays of pointers.
 Move until the last common element of both the arrays is found.
 Prints its data. that is the Lowest Common Ancestor

 The algorithm is of the order of height of tree... O((h).Since you have to iterate from root to the node of the element to find its path.
*/

#include <iostream>
#include <stdlib.h>

using namespace std;

// declaring struct node data structure for binary tree
struct node{
    int data;
    struct node* left;
    struct node* right;
};

// create a node of binary tree
struct node* create(int data)
{
    struct node* newNode=new node;
    newNode->data=data;
    newNode->left=newNode->right=NULL;
    return newNode;
}

// insert new node in the binary tree
struct node* insertNode(struct node* root,int data)
{


    if(root==NULL)
    {
        root=create(data);

    }
    else if(data<=root->data)
    {
        root->left=insertNode(root->left,data);

    }
    else
    {
        root->right=insertNode(root->right,data);
    }

    return root;
}

// find the series of pointers to the nodes throughout the path from root to the element v
bool findpath(struct node* root,int v,struct node* path[],int j)
{
    if(root==NULL)      // if binary tree empty
    {
        return false;
    }
    path[j]=root;       // put the address in array of pointers

    if(root->data==v)   // if element found
    {
        return true;
    }
    if (((root->left)&&findpath(root->left,v,path,j+1)) || ((root->right)&&findpath(root->right,v,path,j+1)))
    {
        return true;
    }

    return false;
}


int main()
{
    int i,j;

    struct node* root=NULL;

    for(i=0;i<100;i++)
    {
        root=insertNode(root,rand()%100);   // creating a binary tree of 100 elements
    }

    // dynamically declaring two arrays to pointers to store path of two elements
    struct node** pathv= (struct node**)malloc(100*sizeof(struct node*));
    struct node** pathw= (struct node**)malloc(100*sizeof(struct node*));

    //initialization
    for(i=0;i<100;i++)
    {
        pathv[i]=0;
        pathw[i]=0;
    }
    int v,w;
    // take inputs for v and w
    do{
    cout<<"v=   ";
    cin>>v;
    if(!(findpath(root,v,pathv,0)))
        cout<<v<<" Not Found in the binary tree. Enter another v"<<endl;
    }
    while(!(findpath(root,v,pathv,0)));

    do{
    cout<<"w=   ";
    cin>>w;
    if(!(findpath(root,w,pathw,0)))
        cout<<w<<" Not Found in the binary tree. Enter another w"<<endl;
    }
    while(!findpath(root,w,pathw,0));

    // finding the path for u and v
    findpath(root,v,pathv,0);
    findpath(root,w,pathw,0);

    j=0;

    // move the index of the array to the last common element
    while(pathv[j]==pathw[j] && findpath(root,v,pathv,0) && findpath(root,w,pathw,0))
    {
        j+=1;
    }
    cout<<"LCA = "<<pathv[j-1]->data<<endl;     //print LCA


    return 0;

}
