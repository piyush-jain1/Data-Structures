/*
Name - PIYUSH JAIN
Roll No. -150101046
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
    struct node* newNode = new node;
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
    else if(data<root->data)
    {
        root->left=insertNode(root->left,data);
    }
    else
    {
        root->right=insertNode(root->right,data);
    }
    return root;
}

// function to calculate the number of leaf nodes
int leafNodes(struct node* root)
{

    if(root==NULL)  return 0;
    if(root->left==NULL && root->right==NULL)       // if right child and left child both are NULL
    {
        return 1;
    }
    return leafNodes(root->left)+leafNodes(root->right);    // else recursively go to left subtree and right subtree


}


int main()
{
    struct node* root;
    int i,j,leaf[50];
    for(i=0;i<50;i++)
    {
        //generating 50 binary trees
        root=NULL;
        for(j=0;j<100;j++)
        {
            root=insertNode(root, rand()%100);      // putting random numbers as data
        }
        leaf[i]=leafNodes(root);    // calculating no of leaf nodes for each tree using function
    }

    // printing the the no. of leaf nodes for each tree
    cout<<"Tree No. --->  "<<"No. of leaf nodes"<<endl;

    for(i=0;i<50;i++)
    {
        cout<<" "<<i+1<<"      --->         "<<leaf[i]<<endl;
    }
    return 0;
}
