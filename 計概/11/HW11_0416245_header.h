#include<stdio.h>
#include<stdlib.h>
struct node{
int data;
struct node *next;
};
struct node *previous,*current;
struct node *insert(int value,struct node *head);
struct node *reverse(struct node *head);
struct node *Remove(struct node *head);
void traverse(struct node *head);
