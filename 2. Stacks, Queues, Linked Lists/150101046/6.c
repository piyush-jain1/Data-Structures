/*
Name - Piyush Jain
Roll No. - 150101046
*/

#include <stdio.h>
#include <stdlib.h>

// declaring struct data type node for linked list
struct node{
    int data;
    struct node* link;
} ;
// creating new node
struct node* create()
{
    struct node* new=(struct node*)malloc(sizeof(struct node));
    return new;
}
//push element in linked list
struct node * push(struct node* head, int x)
{
    struct node* new=create();
    new->data=x;
    new->link=head;
    head=new->link;
    return new;
}
// function to find if there is any loop
void findLoop(struct node* head)
{
    struct node* temp1=head;
    struct node* temp2=head;
    temp1=temp1->link;
    temp2=temp2->link->link;
    while(temp1 && temp2 && temp2->link )
    {
        temp1=temp1->link;
        temp2=temp2->link->link;
        if(temp1==temp2)
        {
            printf("Yes\n");
            return;
        }
    }
    printf("No\n");
    return;

}
int main()
{
    struct node* head=NULL;

    // pushing elements in Linked List
    head=push(head,5);
    head=push(head,9);
    head=push(head,7);
    head=push(head,4);
    head=push(head,1);



    //Creating loop to check
    head->link->link->link->link=head->link;


    // check if there is any loop
    findLoop(head);


    return 0;
}
