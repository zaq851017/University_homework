#include "HW11_0416245_header.h"

int main(){
struct node *head = NULL;
printf("Input the number of data you want to insert: ");
int N,i;
scanf("%d", &N);
printf("Data: ");
for (i = 0; i < N; i++) {
int t;
scanf("%d", &t);
//1.(1)
head = insert(t, head);
}
//1.(2)
printf("After insert: ");
traverse(head);
//2.(1)
head =reverse(head);
printf("After reverse:");
//2.(2)
traverse(head);
head =reverse(head);
printf("After remove:");
Remove(head);
traverse(head);
free(head);
return 0;
}
