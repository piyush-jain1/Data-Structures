/*
Name - Piyush Jain
Roll No. - 150101046
*/

/*
Assignment 10 , Question 2 :
This program takes two polynomials as input in the form of list of coefficient-exponent pairs.
It finds the product term wise and hash the coefficients as per the exponents.
It finally prints the product polynomial in the form of list of coefficient-exponentt pair.
*/

/*
Sample Input :

Enter no of terms in Polynomial 1 and Polynomial 2 respectively : 3 5
Enter 3 terms as [coeff,exp] for Polynomial 1: 
4 8
9 2
6 7
Enter 5 terms as [coeff,exp] for Polynomial 2: 
5 6
1 2
3 7
8 9
6 4

Sample Output :

Resultant [coeff,exp] for P1*P2 : 
[9,4]
[54,6]
[45,8]
[33,9]
[4,10]
[108,11]
[24,12]
[30,13]
[38,14]
[12,15]
[48,16]
[32,17]
*/

#include <iostream>

using namespace std;

// struct for each term
struct term {
	int coeff;
	int exp;
	struct term * next;
};

// hash function
int hash_function(int a,int b)
{
	return a+b;
}

int main()
{	
	// create and initialize two polynomials
	struct term * P1 = new term;
	struct term * P2 = new term;
	P1->coeff = 0;
	P1->exp = 0;
	P1->next = NULL;
	P2->coeff = 0;
	P2->exp = 0;
	P2->next = NULL;

	// take M and N ,i.e., the sizes of each polynomial,as input
	int m,n;
	cout<<"Enter no of terms in Polynomial 1 and Polynomial 2 respectively : ";
	cin>>m>>n;
	int i=m,j=n;
	int c,e;

	struct term * newTerm = NULL;
	int degree1 = 0, degree2 = 0;

	// create polynomial term by term and maintaining it as a Linked List
	cout<<"Enter "<<m<<" terms as [coeff,exp] for Polynomial 1: "<<endl;
	while(i--)
	{	
		// taking coefficient-exponent pair as input
		cin>>c>>e;
		newTerm = new term;
		newTerm -> coeff = c;
		newTerm -> exp = e;
		if(e > degree1)
		{
			degree1 = e;
		}
		newTerm -> next = NULL;
		newTerm->next = P1->next;
		P1->next = newTerm;
	}

	// create polynomial term by term and maintaining it as a Linked List
	cout<<"Enter "<<n<<" terms as [coeff,exp] for Polynomial 2: "<<endl;
	while(j--)
	{	
		// taking coefficient-exponent pair as input
		cin>>c>>e;
		newTerm = new term;
		newTerm -> coeff = c;
		newTerm -> exp = e;
		if(e > degree2)
		{
			degree2 = e;
		}
		newTerm -> next = NULL;
		newTerm->next = P2->next;
		P2->next = newTerm;
	}

	// size of hash table
	int size = degree1+degree2+1;
	int hash[size];

	// initialize hash table
	for(i=0;i<size;i++)
	{
		hash[i]=0;
	}
	
	// find the product of polynomials term-wise and put the coefficients into the hash table as hashed by their exponenents
	struct term * temp1 = P1;
	while(temp1->next!=NULL)
	{	
		temp1 = temp1->next;
		struct term * temp2 = P2;
		while(temp2->next!=NULL)
		{	
			temp2 = temp2->next;
			int index = temp1->exp + temp2->exp;
			hash[index] += (temp1->coeff * temp2->coeff);
		}
	}

	// Print the resultant polynomial as list of coefficient-exponent pair
	cout<<"Resultant [coeff,exp] for P1*P2 : "<<endl;
	for(i=0;i<size;i++)
	{
		if(hash[i]!=0)
		{	
			cout<<"["<<hash[i]<<","<<i<<"]"<<endl;
		}
	}

	return 0;

}