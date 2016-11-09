/*
Name - Piyush Jain
Roll No. - 150101046
*/

/*
Assignment 10 , Question 3 :
This program 
(a) Creates a binary search tree of books with given details.
(b) Increases cost of each book by 10 percent
(c) Prints the number of copies sold for a given ISBN.
(d) Adds a new node to the Binary Search Tree
*/

/*
Sample Output :
[book1,978-92-95055-2-5]
[book3,978-88-84455-5-3]
[book4,979-91-85953-4-1]
[book2,979-97-95752-3-9]
[book5,978-95-95459-7-8]
[book1,978-92-95055-2-5]
[book3,978-88-84455-5-3]
[book4,979-91-85953-4-1]
[book2,979-97-95752-3-9]
[book5,978-95-95459-7-8]
2000
[book1,978-92-95055-2-5]
[book3,978-88-84455-5-3]
[book4,979-91-85953-4-1]
[book2,979-97-95752-3-9]
[book5,978-95-95459-7-8]
[NEWBOOK,979-94-95523-6-4]
*/

#include <iostream>

using namespace std;

// struct for ISBN-Number of book
struct ISBN_num{
	int EAN;
	int reg_group;
	int registrant;
	int publication;
	int check;
};


// struct for nodes of Binary Search Tree
struct node{
	struct node * left;
	struct node * right;
	struct ISBN_num ISBN;
	const char * title;
	const char * author;
	int year;
	int cost;
	int copies_sold;
};

// function to create new node with given data
struct node* create(int EAN,int reg_group,int registrant,int publication,int check,const char * title,const char * author,int year,int cost,int copies_sold)
{
    struct node* newNode = new node();
    newNode->ISBN.EAN = EAN;
    newNode->ISBN.reg_group = reg_group;
    newNode->ISBN.registrant = registrant;
    newNode->ISBN.publication = publication;
    newNode->ISBN.check = check;
    newNode->title = title;
    newNode->author = author;
    newNode->year = year;
    newNode->cost = cost;
    newNode->copies_sold = copies_sold;
    newNode->left=newNode->right=NULL;
    return newNode;
}

// utility function to compare two ISBN , returns 1 if ISBN1 is less than ISBN2 and returns 2 if ISBN2 is less than ISBN1
int compareISBN(struct ISBN_num ISBN1,struct ISBN_num ISBN2)
{	
	int flag = 1;
	// repeatedly compare starting from Most Significant digit to the Least Significant Digit
	if(ISBN1.EAN < ISBN2.EAN)
	{
		flag=1;
	}
	else if(ISBN1.EAN < ISBN2.EAN)
	{
		flag=2;
	}
	else
	{
		if(ISBN1.reg_group < ISBN2.reg_group)
		{
			flag=1;
		}
		else if(ISBN1.reg_group > ISBN2.reg_group)
		{
			flag=2;
		}
		else
		{
			if(ISBN1.registrant < ISBN2.registrant)
			{
				flag=1;
			}
			else if(ISBN1.registrant > ISBN2.registrant)
			{
				flag=2;
			}
			else
			{
				if(ISBN1.publication < ISBN2.publication)
				{
					flag=1;
				}
				else if(ISBN1.publication > ISBN2.publication)
				{
					flag=2;
				}
				else
				{
					if(ISBN1.check < ISBN2.check)
					{
						flag=1;
					}
					else if(ISBN1.check > ISBN2.check)
					{
						flag=2;
					}
					else
					{
						flag=0;
					}
				}
			}
		}
	}

	return flag;
}

// function to insert new node in binary search tree
struct node* ADD_NEW_BOOK(struct node* root,struct node * newNode)
{
    struct node * y =NULL;
    struct node * temp = root;

    // reach till the leaf node
    while(temp!=NULL)
    {
    	y = temp;
    	if(compareISBN(newNode->ISBN,y->ISBN)==1)
    	{
    		temp=temp->left;
    	}
    	else if(compareISBN(newNode->ISBN,y->ISBN)==2)
    	{
    		temp=temp->right;
    	}
    }

    // if tree was empty initially
    if(y==NULL)
    {
    	root =  newNode;
    }
    else if(compareISBN(newNode->ISBN,y->ISBN)==1)
    {
    	y->left = newNode;
    }
    else if(compareISBN(newNode->ISBN,y->ISBN)==2)
    {
    	y->right = newNode;
    }

    return root;

}

// Utility function to Print the Binary Search Tree as per InOrder Traversal
void Print(struct node * root)
{
	if(root!=NULL)
	{	
		// print the title and ISBN of each book
		cout<<"["<<root->title<<","<<root->ISBN.EAN<<"-"<<root->ISBN.reg_group<<"-"<<root->ISBN.registrant<<"-"<<root->ISBN.publication<<"-"<<root->ISBN.check<<"]"<<endl;
		Print(root->left);
		Print(root->right);
	}
}

// Utility function to increase cost of each book by 10 percent
struct node * INCREASE_10_PERCENT(struct node * root)
{	
	if(root!=NULL)
	{
		(root->cost) += 0.1*(root->cost);
		INCREASE_10_PERCENT(root->left);
		INCREASE_10_PERCENT(root->right);
	}
	return root;
}

// utility function that returns number of copies sold for a given ISBN
int COPIES_SOLD(struct node * root,struct ISBN_num findISBN)
{	
	if(root!=NULL)
	{
		struct node * temp = root;
		// traverse until the ISBN is found or the the completion of traversal
		while(temp!=NULL && (temp->ISBN.EAN!=findISBN.EAN) || (temp->ISBN.reg_group!=findISBN.reg_group) || (temp->ISBN.registrant!=findISBN.registrant) || (temp->ISBN.publication!=findISBN.publication) || (temp->ISBN.check!=findISBN.check) ) 
		{
			if(compareISBN(findISBN,temp->ISBN)==1)
			{
				temp = temp->left;
			}
			else if(compareISBN(findISBN,temp->ISBN)==2)
			{
				temp = temp->right;
			}
			// if ISBN is not found until end
			if(temp==NULL)
			{
				return -1;
			}
		}
		// if ISBN is found , return its number of copies
		return temp->copies_sold;
	}
}


int main()
{	
	struct node * root = NULL;
	struct node * newBook[10];
	
	int i;
	
	// creating nodes to be inserted in the Binary Search Tree
	newBook[0] = create(978,92,95055,02,5,"book1","author1",1980,500,2500);
	newBook[1] = create(979,97,95752,03,9,"book2","author2",1985,250,2000);
	newBook[2] = create(978,88,84455,05,3,"book3","author3",1990,300,1500);
	newBook[3] = create(979,91,85953,04,1,"book4","author4",1995,400,1700);
	newBook[4] = create(978,95,95459,07,8,"book5","author5",2000,450,1200);

	// Insert nodes in the Binary Search tree
	for(i=0;i<5;i++)
	{
		root  = ADD_NEW_BOOK(root,newBook[i]);
	}

	// print the tree
	Print(root);

	// increase the cost of each book by 10 percent
	root = INCREASE_10_PERCENT(root);

	// print the tree
	Print(root);

	// create a new ISBN
	struct ISBN_num findISBN;
	findISBN.EAN=979;
	findISBN.reg_group=97;
	findISBN.registrant=95752;
	findISBN.publication=03;
	findISBN.check=9;

	// print the number of copiies sold for the given ISBN
	cout<<COPIES_SOLD(root,findISBN)<<endl;

	// create a new node to be added into the tree
	struct node * book = create(979,94,95523,06,4,"NEWBOOK","NEWAUTHOR",2005,200,2200);
	
	// add a new node into the tree
	root = ADD_NEW_BOOK(root,book);

	// print the tree
	Print(root);

	return 0;

}

