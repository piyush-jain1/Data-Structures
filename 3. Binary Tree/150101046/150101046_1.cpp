/*
Name - Piyush Jain
Roll No. - 150101046
*/

#include <iostream>
#include <stdlib.h>
#include <queue>


using namespace std;

// declaring struct node data structure for binary tree
struct node{
    int data;
    struct node* left;
    struct node* right;
};

// function to create new node with input data
struct node* create(int data)
{
    struct node* newNode = new node();
    newNode->data=data;
    newNode->left=newNode->right=NULL;
    return newNode;
}

// function to insert new node in binary tree
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

// function to find level of current pointer i.e. key in the binary tree (considering level of root as 0)
int findLevel(struct node* root,struct node* key,int level)
{
    if(root==NULL)  return -1;
    if(root==key)
    {
        return level;
    }

    int l=findLevel(root->left,key,level+1);
    if(l!=-1)   return l;
    else
        return findLevel(root->right,key,level+1);
}

// function to find level of leaf node with largest level
int leafNodeMax(struct node* root)
{
    static int maxlevel=0;
    if(root==NULL)  return -1;  //empty binary tree
    queue<node *> q;    //declaring queue to store address of nodes
    q.push(root);       // pushing address of root in queue
    while(!q.empty())
    {
        node* current= q.front();   // storing current node address
        if(current->left==NULL && current->right==NULL)     // if leaf node is found
        {
            maxlevel=findLevel(root,current,0);     // update maxlevel by finding the level of that current address in the binary tree
        }
        if(current->left!=NULL) q.push(current->left);      // push the left node's address into the queue
        if(current->right!=NULL)    q.push(current->right);     // push the right node's address into the queue
        q.pop();        // pop out the front element (current)

    }
    return maxlevel;
}

// function to find level of leaf node with largest level
int leafNodeMin(struct node* root)
{
    static int minlevel=100;
    if(root==NULL)  return -1;      //empty binary tree
    queue<node *> q;        //declaring queue to store address of nodes
    q.push(root);       // pushing address of root in queue
    while(!q.empty())
    {
        node* current=q.front();        // storing current node address
        if(current->left==NULL && current->right==NULL)      // if leaf node is found
        {
            if(findLevel(root,current,0)<minlevel)
            {
                minlevel=findLevel(root,current,0);     // update minlevel by finding the level of that current address in the binary tree only if new value is smaller than the previous value
                break;
            }
        }
        if(current->left!=NULL) q.push(current->left);        // push the left node's address into the queue
        if(current->right!=NULL)    q.push(current->right);     // push the right node's address into the queue
        q.pop();        // pop out the front element (current)
    }
    return minlevel;
}

int main()
{
    struct node* root=NULL;
    int i,j;
    int diff[50],counter[100];
    for(j=0;j<50;j++)       // making 50 binary trees
    {
        root=NULL;      // initializing tree as empty

        for(i=0;i<100;i++)
        {
            root=insertNode(root,rand()%100);       // inserting 100 random numbers in the binary tree
        }

        diff[j]=leafNodeMax(root)-leafNodeMin(root);        // calculating the difference between  max value and min value of level of leaf node
    }
    for(i=0;i<100;i++)
    {
        counter[i]=0;
        for(j=0;j<50;j++)
        {
            if(diff[j]==i)
            {
                counter[i]++;   // counting the frequency of differences
            }
        }
    }

    cout<<"Difference   --->    No. of runs"<<endl;

    for(i=0;i<100;i++)
    {
        if(counter[i]!=0)
            cout<<i<<"    --->    "<<counter[i]<<endl;         // printing the differences

    }

    return 0;
}
