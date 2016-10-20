/*
Name - Piyush Jain
Roll No. - 150101046
*/

/*
The problem is to find the diameter of a binary tree.
The algorithm which has been used is :
Find the height of the left subtree.
Find the height of the right subtree.
Find the longest path between leaves that goes through the root of tree.
The maximum of all these will be the diameter of tree.
The algorithm is of the order of n i.e. O(n).
We are calculating the height of subtrees and updating the value of left and right diamteres recursively and getting the max of all these.
*/

#include <iostream>
#include <stdlib.h>


using namespace std;

// declaring struct node data structure for binary tree
struct node {
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

int diameter(struct node* root, int * height)
{   
    //initializing
    int lheight=0;      //height of left subtree
    int rheight=0;      //height of right subtree
    int ldiameter=0;        // diameter of left subtree
    int rdiameter=0;        //diameter of right subtree

    if(root==NULL)
    {
        *height=0;      // empty tree, diameter equal to zero
        return 0;
    }

    // get the height of left and right subtrees and store in ldiameter and rdiameter
    ldiameter = diameter(root->left, &lheight);     
    rdiameter = diameter(root->right, &rheight);

    // height of current node is one more than the max of height of left and subtree
    *height = max(lheight,rheight)+1;

    return max(lheight+rheight+1,max(ldiameter,rdiameter));
}
int main()
{
    int i,j;

    struct node* root=NULL;
    cout<<"Tree No.--->Tree Diameter"<<endl;
    for(j=0;j<50;j++)   // generating 50 binary trees
    {   root=NULL;
        for(i=0;i<100;i++)      // inserting 100 elements in each tree
        {
            root=insertNode(root,rand()%100);   // creating a binary tree of 100 elements
        }
        int height=0;   //initialize height
        int tree_diameter = diameter(root,&height);     // get tree tree_diameter
        cout<<j+1<<"     --->     "<<tree_diameter<<endl;      // print tree diameter
    }
    return 0;
}
