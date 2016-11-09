/*
Name - PIYUSH JAIN
Roll No. - 150101046
*/

/*
Assignment - 8
This is a program on Binomial Heap.
This program first processes data from a file "binomialHeapTest.txt" and gives the output.
Then, this program shows a command based interface.
It takes command from user and do following operations as per the commands :
MAKE-BINOMIAL-HEAP
BINOMIAL-HEAP-UNION
BINOMIAL-HEAP-INSERT
BINOMIAL-HEAP-EXTRACT-MIN
SHOW-BINOMIAL-HEAP
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#define MAX 100

using namespace std;

// struct declaration for node
typedef struct bnode{
	struct bnode * parent;				
	struct bnode * leftmostchild;
	struct bnode * sibling;
	int key;
	int degree;
} bnode;

// utility function to create an empty binomial heap
bnode * MAKE_BINOMIAL_HEAP ()
{
	bnode * init;
	init=NULL;

	return init;
}

// utility function to link two nodes heirarchichally
void BINOMIAL_LINK ( bnode * next ,  bnode * curr  )
{
	next -> parent = curr;
	next -> sibling = curr -> leftmostchild ;
	curr -> leftmostchild = next ;
	curr -> degree += 1;

}

// utility function to merge two heaps
bnode * MERGE ( bnode * H1 , bnode * H2 )
{
	struct bnode * newHead = MAKE_BINOMIAL_HEAP();

	bnode * temp1 = H1;
	bnode * temp2 = H2;
	bnode * temp;
	
	// initialize new heap to store merged heap
	if(temp1!=NULL)
	{
		if(temp2!=NULL)
		{
			if(temp1->degree <= temp2->degree)
			{
				newHead = temp1;
				temp1=temp1->sibling;
			}	
			else if(temp1->degree > temp2->degree)
			{	
				newHead = temp2;
				temp2=temp2->sibling;
			}
		}

		else
		{
			newHead = temp1;
			temp1=temp1->sibling;
		}
	}
	else 
	{
		newHead = temp2;
		temp2=temp2->sibling;
	}

	temp=newHead;

	// insert the lesser degree nodes from both the heaps repeatedly into the new heap 
	while(temp1!=NULL || temp2!=NULL)
	{	
		if(temp1==NULL)
		{
			temp->sibling=temp2;
			break;
		}
		else if (temp2==NULL)
		{	
			
			temp->sibling=temp1;
			break;
		}

		// whichever node has lesser degree goes next into the new heap
		if(temp1->degree <= temp2->degree)
		{	
			temp->sibling=temp1;
			temp1=temp1->sibling;
		}

		else
		{
			temp->sibling=temp2;
			temp2=temp2->sibling;
		}
		temp=temp->sibling;
		
	}

	// return final merged heap
	return newHead;
}

// utility function to do union of two binomial heaps
bnode * UNION ( bnode * H1 , bnode * H2 )
{	
	// initialize new heap H to store Union
	bnode * H = MAKE_BINOMIAL_HEAP();

	// Merge given heaps
	H = MERGE ( H1, H2 );
	
	// if merged heap is not empty
	if(H!=NULL)
	{

		bnode * prev = NULL;
		bnode * curr = H;
		bnode * next = H->sibling;

		// traverse three pointers on previous , current and next nodes respectively
		while(next!=NULL)
		{	
			// if degree of two nodes are unequal, promote the pointers ahead
			if((curr->degree!=next->degree))
			{
				prev = curr;
				curr = next;
				next = next -> sibling ;
			}

			else 
			{	
				// link the greater key node to the smaller key node and move pointers ahead
				if(curr->key<=next->key)
				{
					curr->sibling=next->sibling;
					BINOMIAL_LINK ( next , curr ) ;
				}
				else 
				{
					if( prev == NULL )
					{
						H = next ;
					}
					else 
					{
						prev -> sibling = next ;
					}
					BINOMIAL_LINK ( curr , next ) ;
					curr = next ;
				}
			}
			next = curr -> sibling ;
		}
		
	}

	return H;

}

// utility function to insert new element in a binomial heap
bnode * INSERT(bnode * H,int keyval)
{	
	// create heap of one element to be inserted
	bnode * H_new = MAKE_BINOMIAL_HEAP();
	bnode * x = new bnode;
	x->key = keyval;
	x->parent = NULL;
	x->leftmostchild = NULL;
	x->sibling = NULL;
	x->degree = 0;
	
	// if original heap is empty, make this new heap as the original heap
	if(H==NULL)
	{	
		H=x;
		
	}
	else
	{	
		// do union of new created single element heap with the original heap
		H_new=x;
		H=UNION(H,H_new);
	}
	
	return H;
}

// utility function to extract minimum value,printing minimum is optional, depends on value of flag
bnode * EXTRACT_MIN(bnode * H,int flag)
{
	bnode * temp = H;

	// if heap is already empty
	if(H==NULL)
	{
		cout<<"Empty Heap , Nothing to extract."<<endl;
		return H;
	}

	bnode * prev = NULL;
	bnode * curr = NULL; 

	// initialize min
	int min = H->key;

	// traverse whole root list and update min, also store the address of min node
	while(temp->sibling!=NULL)
	{
		if(temp->sibling->key < min)
		{
			min = temp->sibling->key;
			prev = temp;
			curr = temp->sibling;
		}
		temp=temp->sibling;
	}

	// if flag is 1, print the extracted min value
	if(flag==1)
	{
		cout<<"Minimum Extraction : "<<min<<endl;
	}

	// remove node conatining min node and store its left most child in childstart
	bnode * childstart = NULL;

	// if min is extracted from first node
	if(prev==NULL && curr==NULL)
	{	
		if(H->sibling==NULL && H->leftmostchild==NULL)
		{
			H=NULL;
			return H;
		}
		childstart = H->leftmostchild;
		H = H->sibling;
	}

	// if min is extracted from last node
	else if(curr->sibling==NULL)
	{	
		childstart = curr->leftmostchild;
		prev->sibling=NULL;
		
	}

	else
	{	
		childstart = curr->leftmostchild;
		prev->sibling=curr->sibling;

	}

	bnode * next = NULL;
	curr = childstart;
	prev=NULL;
	bnode * H1 = NULL;

	// if min node has no child
	if(childstart!=NULL)
	{	
		bnode * next = NULL;
		curr = childstart;
		prev=NULL;

		// reverse pointers of list of children , thus creating another binomial heap 
		while(curr!=NULL)
		{
			next = curr->sibling;
			if(next==NULL)
			{
				H1 = curr;
			}
			curr->sibling = prev;
			prev = curr;
			curr = next;
		}
	}

	// join the two binomial heaps
	H = UNION(H,H1);

	return H;
}

// function to print the nodes of heap in correct order
void showHeap(bnode * x,int depth)
{
	if(x->sibling!=NULL)
	{
		showHeap(x->sibling,depth);
	}

	int i;
	if(x->parent==NULL)
	{	
		
		cout<<x->key;
		
	}
	else
	{
		if(x->leftmostchild!=NULL)
		{
			for(i=1;i<=(8*depth);i++)
			{
				cout<<" ";
			}
			cout<<x->key;
			if(x->leftmostchild==NULL)
			{
				cout<<endl;
			}
		}
		else
		{
			for(i=1;i<=7;i++)
			{
				cout<<" ";
			}
			cout<<x->key<<endl;
		}
	}
	
	
	if(x->leftmostchild!=NULL)
	{
		showHeap(x->leftmostchild,depth+1);
	}

}

// utility function to display the binomial heap rotated 90 degrees counter-clockwise
void showBinomialHeap(bnode * H)
{
	cout<<endl<<"Structure of Binomial Heap (rotated 90 degrees counter-clockwise) :"<<endl<<endl;
	if( H == NULL)
	{
		cout<<"Empty Heap"<<endl<<endl;
		return;
	}
	cout<<endl<<endl<<"-----------------------------------------"<<endl;
	showHeap(H,0);
	cout<<endl<<"-----------------------------------------"<<endl<<endl;
}

int main()
{	

	cout<<"---------------BINOMIAL HEAP---------------"<<endl<<endl;

	
	ifstream fin;
   	char query ;
   	int val;
	int flag;
   	bnode * headnode = NULL;

   	cout<<"---------Processing input data from file---------"<<endl<<endl;

   	// processing test file
	fin.open("binomialHeapTest.txt", ios::in);
	while (!fin.eof() ) {
		fin.get(query);
		if(query == 'c')
		{
			headnode=MAKE_BINOMIAL_HEAP();
		}
		else if(query=='i')
		{
			fin>>val;
			headnode=INSERT(headnode,val);
		}
		else if(query=='S')
		{
			showBinomialHeap(headnode);
		}
		else if(query=='-')
		{
			flag=0;
		}
		else if(query=='+')
		{
			flag=1;
		}
		else if(query=='d')
		{
			headnode=EXTRACT_MIN(headnode,flag);
		}
	}
	

	// Now user interface

	cout<<endl<<endl<<"---------Command Based User Interface---------"<<endl<<endl;

	int i;

	// array of head nodes
	bnode * head[MAX];
	

	// printing list of menu commands
	cout<<endl<<endl<<"Menu of Commands for different operations : "<<endl;
	cout<<"__________________________________________"<<endl<<endl;

	cout<<"(1.)For MAKE-BINOMIAL-HEAP			:		Press 'c'"<<endl;
	cout<<"(2.)For BINOMIAL-HEAP-UNION			:		Press 'u'"<<endl;
	cout<<"(3.)For BINOMIAL-HEAP-INSERT			:		Press 'i'"<<endl;
	cout<<"(4.)For BINOMIAL-HEAP-EXTRACT-MIN"<<endl<<"	(with print key flag on)		:		Press 'E'"<<endl;
	cout<<"(5.)For BINOMIAL-HEAP-EXTRACT-MIN"<<endl<<"	(with print key flag off)		:		Press 'e'"<<endl;
	cout<<"(6.)For SHOW-BINOMIAL-HEAP			:		Press 's'"<<endl;
	cout<<"(7.)Exit the Program				:		Press '0'"<<endl<<endl;

	cout<<"------------------------------------------------------------"<<endl;

	int k=-1,p=0,q=0;

	// take command as query and do accordingly
	while(1)
	{	
		// take command from user
		cout<<endl<<"Enter your Command  : ";
		cin>>query;

		// exit command
		if(query=='0')
		{
			cout<<"Exiting the program"<<endl;
			return 0;
		}

		// create new binomial heap
		else if(query=='c')
		{	
			k++;
			head[k] = MAKE_BINOMIAL_HEAP();
			cout<<"Heap with head pointer as 'head["<<k<<"] is created. Use this index as heap ID"<<endl<<endl;
		}

		// do union of two binomial heaps
		else if(query=='u')
		{
			if(k==-1)
			{
				cout<<"No heap available for Union, Please make binomial heap first."<<endl<<endl;
			}
			else if(k==0)
			{
				cout<<"There is only one heap already."<<endl<<endl;
			}
			else
			{	
				do
				{
					cout<<"Enter two distinct valid heap IDs to join : ";
					cin>>p;
					cin>>q;
				}while(p>k || q>k || p<0|| q<0);	
				
				head[p]=UNION(head[p],head[q]);
				head[q]=NULL;
				cout<<"Union of heap["<<p<<"] and heap ["<<q<<"] is done"<<endl;
				cout<<"Head for joined heap is head["<<p<<"]."<<endl<<endl;
			}
		}

		// insert new element
		else if(query=='i')
		{
			if(k==-1)
			{
				cout<<"No heap available for Insertion, Please make binomial heap first."<<endl<<endl;
			}
			else
			{	
				do
				{
					cout<<"Enter valid heap ID in which you want the new value to be inserted : ";
					cin>>p;
				}while(p>k ||  p<0);
				cout<<"Enter an integer value to be inserted : ";
				cin>>q;
				head[p]=INSERT(head[p],q);
				cout<<q<<" inserted into heap["<<p<<"]."<<endl<<endl;
			}
		}

		// extract min from the binomial heap
		else if(query=='E' || query=='e')
		{
			if(k==-1)
			{
				cout<<"No heap available for Extraction, Please make binomial heap first."<<endl<<endl;
			}
			else
			{	
				do
				{
				cout<<"Enter valid heap ID from which you want to extract minimum value : ";
				cin>>p;
					
				}while( p>k || p<0 );
				if(query=='E')
				{
					flag=1;
				}
				else
				{
					flag=0;
				}

				head[p]=EXTRACT_MIN(head[p],flag);
				cout<<"Minimum Extraction done from heap["<<p<<"]"<<endl;
			}
		}

		// show binomial heap
		else if(query=='s')
		{
			if(k==-1)
			{
				cout<<"No heap available for Showing, Please make binomial heap first."<<endl<<endl;
			}
			else
			{
				do
				{
					cout<<"Enter valid heap ID which you want to display : ";
					cin>>p;
					
				}while(p>k || p<0);
				
				showBinomialHeap(head[p]);	
			}
		}

		// error prompt for all other inputs
		else
		{
			cout<<"Invalid Command. Enter again."<<endl<<endl;
		}		
	}
	
	return 0;

}

