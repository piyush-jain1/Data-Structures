#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>

#define MAX 100

using namespace std;

struct node {
    int key;
    int degree;
    struct node * parent;
    struct node * child;
    struct node * left;
    struct node * right;
    int mark;
} ;


struct node * MAKE_HEAP()
{
    struct node * fnode = NULL ;
    return fnode;    
}

struct node * INSERT ( struct node * min , int k )
{    
    struct node * newNode = new node;
    
    newNode -> key = k;
    newNode -> degree = 0;
    newNode -> parent = NULL;
    newNode -> child = NULL;
    newNode -> left = newNode;
    newNode -> right = newNode;
    newNode -> mark = 0;

    if( min == NULL )
    {
        min = newNode;
    }

    else 
    {
        struct node * temp ;
        temp = min->right ;
        min ->right = newNode ;
        newNode ->right = temp;
        temp ->left = newNode ;
        newNode -> left = min ;
        
        
        if ( newNode->key < min->key )
        {
            min = newNode;
        }
    }
    
    return min ;
}

// utility function to count the number of nodes
int numberOfNodes ( struct node * min )
{
int count = 0 ;
if ( min!=NULL )
{
struct node * temp = min;
do
{
count++;
temp = temp->right;
}while(temp!=min);
}
return count ;
}


struct node * UNION ( struct node * min1 , struct node * min2 )
{

    if ( min1 != NULL && min2 != NULL )
    {
        struct node * temp1;
        struct node * temp2;
        temp1 = min1 -> right ;
        min1 -> right = min2 ;
        temp2 = min2 -> left ;
        temp2 -> right = temp1 ;
        temp1 -> left = temp2 ;
        min2 -> left = min1 ;
        if( min2 -> key < min1 -> key )
        {
        return min2 ;
        }
        return min1 ;
    }
    else if ( min1 != NULL )
    {
        return min1;
    }
    else if ( min2 != NULL )
    {
        return min2;
    }

}
// utility function to make min2 as child of min1
struct node * CREATE_CHILD ( struct node * min1 , struct node * min2 )
{

    if ( min1!=NULL && min2!=NULL )
    {
        min1 -> degree += numberOfNodes ( min2 );
        struct node * temp = min2;
        do
        {
            temp -> parent = min1;
            temp = temp->right ;
        }while(temp!=min2);

        if(min1 -> child == NULL )
        {
            min1 -> child = min2;
        }

        else
        {
            min1->child=UNION ( min1->child , min2 ) ;
        }


    }

    return min1;

}

struct node * HEAP_LINK ( struct node * min , struct node * y , struct node * x )
{
    if( min != NULL )
    {

    // if node to be removed is minimum
    if ( min == y )
    {
        struct node * find = min ;
        do
        {
            int minimum = 1000000;
            if( find->key <  minimum && find!=min )
            {
                minimum = find->key;
                min = find;
            }
            find = find -> right ;
        }while(find!=x);
    }

    struct node * temp = y;
    y -> right -> left = temp -> left ;
    y -> left -> right = temp -> right ;
    y -> left = y ;
    y -> right = y ;
    y -> mark = 0 ;
    min = CREATE_CHILD ( x , y ) ;


    }
    return min ;  
}


void Print ( struct node * min )
{
    if ( min!=NULL )
    {
        cout<<"Circular Doubly Linked List : "<<endl;
        struct node * temp = min;
        do
        {
            cout<<"["<<temp->key<<" , "<<temp->degree<<"]"<<endl;
            
            temp = temp->right;
        }while(temp!=min);

        cout<<endl;
    }
    else
    {
        cout<<"Empty Heap"<<endl;
    }
}

/*
struct node * findMin ( struct node * H )
{
    struct node * find = H;
    struct node * min = NULL;
    int minimum = 100000000;
    do
    {
        if(find->key < minimum)
        {
            minimum = find->key;
            min = find;
        }
        find = find->right;
    }while(find!=H);

    return min;

}
*/

struct node * CONSOLIDATE ( struct node * H )
{
    int i;
    struct node * A[MAX];
    for(i=0;i<MAX;i++)
    {
        A[i]=NULL;
    }

    
    struct node * x = H;
    struct node * y;
    struct node * temp = x;
    int d;

    do
    {   
        temp = temp->right;
        d = x->degree;
        while(A[d]!=NULL)
        {
            y=A[d];
            if(x->key > y->key)
            {
                struct node * swapper = x;
                x=y;
                y=swapper;

            }
            
            if(y==H)
            {
                H=x;
            }
            HEAP_LINK(H,y,x);
            if(x->right==x)
            {
                H=x;
                A[d]=NULL;
            }
            d=d+1;
        }

        A[d]=x;
        
        x=x->right;
    
    
          
    }while(x!=H);
    /*
    
    struct node * H1 =NULL;

    for(i=0;i<=MAX;i++)
    {
        if(A[i]!=NULL)
        {
            A[i]->left = A[i];
            A[i]->right = A[i];
            if(H1!=NULL)
            {
                H1->left->right = A[i];
                A[i]->right = H1;
                A[i]->left = H1->left;
                H1->left = A[i];
                if(A[i]->key < H1->key)
                {
                    H1 = A[i];
                }
                //cout<<"Key = "<<H1->key<<endl;
                
            }
            else
            {
                H1=A[i];
            }
           
        }
    }

    */
    
    //Print(H);
    return H;

}

struct node * EXTRACT_MIN (struct node * H,int flag)
{
    if(H==NULL)
    {
        cout<<"Empty Heap !"<<endl;
        return NULL;
    }
    if(flag==1)
    {
        cout<<"Min : "<<H->key<<endl;
    }
    
    struct node * childlist = H->child;
    struct node * p;
    struct node * temp;
    if(childlist!=NULL)
    {   
        p = childlist;
        do
        {
            temp=childlist->right;
            H->left->right=childlist;
            childlist->right=H;
            childlist->left=H->left;
            H->left=childlist;
            if(childlist->key < H->key)
                H=childlist;
            childlist->parent=NULL;
            childlist = temp;
        }while(temp!=p);
    }



    
    H->left->right=H->right;
    H->right->left=H->left;
    if(H==H->right && H->child==NULL)
    {
        H=NULL;
    }
    else
    {   
        H=H->right;
        H=CONSOLIDATE(H);
    }
    //Print(H);
    return H;
    
}


int main()
{
    cout<<"----------------FIBONACCI HEAP----------------"<<endl<<endl;

    cout<<"MENU OF COMMANDS"<<endl;

    cout<<"MAKE_HEAP    :       Press 'c'"<<endl;
    cout<<"INSERT       :       Press 'i'"<<endl;
    cout<<"Extract_Min  :       Press 'e'"<<endl;
    cout<<"UNION        :       Press 'u'"<<endl;
    cout<<"SHOW_HEAP    :       Press 'S'"<<endl;

    cout<<"Taking Input from file"<<endl;
   
    ifstream fin;
    char query ;
    int val;
    int flag;
    struct node * headnode = NULL;

    cout<<"---------Processing input data from file---------"<<endl<<endl;

    // processing test file
    fin.open("test1.txt.txt", ios::in);
    while (!fin.eof() ) {
        fin.get(query);
        if(query == 'c')
        {
            headnode=MAKE_HEAP();
        }
        else if(query=='i')
        {
            fin>>val;
            headnode=INSERT(headnode,val);
        }
        else if(query=='S')
        {
            Print(headnode);
        }
        else if(query=='-')
        {
            flag=0;
        }
        else if(query=='+')
        {
            flag=1;
        }
        else if(query=='e')
        {
            headnode=EXTRACT_MIN(headnode,flag);
        }
    }
    return 0;
}