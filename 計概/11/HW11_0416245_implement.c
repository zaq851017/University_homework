#include "HW_0416245_header.h"

struct node *insert(int value,struct node *head){
current =(struct node *)malloc(sizeof(struct node));
current->data=value;
if(head==NULL){
   head=current;}
else{
   previous->next=current;}
current->next=NULL;
previous=current;
return head;
}

struct node *reverse(struct node *head){
if(head->next==NULL){ return head;}
struct node *former,*latter,*temp;
former=head;
head=head->next;
latter=head->next;
while (latter!=NULL){
head->next=former;
former=head;
head=latter;
latter=head->next;
}
head->next=former;
temp=head;
while(temp->next->next!=temp) temp=temp->next;
temp =temp->next;
temp->next=NULL;
return head;
}


struct node *Remove(struct node *head){
struct node *start;
struct node *headreturn;
struct node *temp;
headreturn=head;
if(head->next==NULL) return headreturn;
start=head->next;
while(1){
   if(start->data==head->data){
    temp=start->next;
    free(start);
    start=temp;
    head->next=start;
    if(head->next==NULL) return headreturn;
   }
   if(start->data!=head->data){
    head=start;
    if(head->next==NULL) return headreturn;
    start=head->next;
   }
}
}

void traverse(struct node *head){
while(head!=NULL){
printf("%d--->",head->data);
head=head->next;
}
printf("NULL\n");
}
