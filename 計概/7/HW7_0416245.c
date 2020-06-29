#include<stdio.h>
#include<stdlib.h>
int n;
/*******************Bubble sort**************************/
void bubble_sort(int n,int a[]){
int i=0,swap;
if(n>=2){
for(i=0;i<(n-1);i++){
    if(*(a+i)>*(a+i+1)){
        swap =*(a+i);
        *(a+i)=*(a+i+1);
        *(a+i+1)=swap;
    }
}
bubble_sort(n-1,a);
}
}
/*****************Quick sort**********************/
void quicksort(int a[],int low,int high){
int middle;
if(low>=high) return ;
middle=spilit(a,low,high);
quicksort(a,low,middle-1);
quicksort(a,middle+1,high);
}

int spilit(int a[],int low,int high){
int memory=a[low];
for( ; ; ){
    while(low<high&&memory<=a[high]){
        high--;
    }
    if(low>=high) break;
    a[low]=a[high];
    low++;

    while(low<high&&memory>=a[low]){
        low++;
    }
    if(low>=high) break;
    a[high]=a[low];
    high--;
}
a[high]=memory;
return high;
}
/********************Merge sort**********************/
void divide(int *a,int beg ,int end){
int mid;
if(beg<end){
    mid = (beg+end)/2;
    divide(a,beg,mid);
    divide(a,mid+1,end);
    mergesort(a,beg,mid,mid+1,end);
}
}
void mergesort(int *a,int lbeg,int lend,int rbeg,int rend){
int cl=lbeg,cr=rbeg,i=lbeg;//控制左右變數和暫存陣列
int moment[n];
while(cl<=lend&&cr<=rend){
    if(a[cl]>a[cr]) moment[i++]=a[cr++];

    else moment[i++]=a[cl++];
}
if(cl>lend){
    while(cr<=rend) moment[i++]=a[cr++];
}
else {
    while(cl<=lend) moment[i++]=a[cl++];
}
for(i=lbeg;i<=rend;i++){
    a[i]=moment[i];
}
}

/****************************************************/
int main(){
int i=0,method;
printf("Given N number:\n");
scanf("%d",&n);
printf("Input:");
int a[n];
while(i<n){
scanf("%d",&*(a+i));
i++;}
printf("0: bubble, 1: quick, 2: merge :");
scanf("%d",&method);
/************************************************/
if(method==0){
    bubble_sort(n,a);
    printf("bubble sort:\n");
    printf("(1)Increasing:\n");
    for(i=0;i<n;i++){
        printf("%d",*(a+i));
        printf(" ");
    }
    printf("\n(2)Decreasing:\n");
    for(i=(n-1);i>=0;i--){
        printf("%d",*(a+i));
        printf(" ");
    }
}
/************************************************/
if(method==1){
quicksort(a,0,n-1);
printf("quicksort:\n");
printf("(1)Increasing:\n");
for(i=0;i<n;i++){
    printf("%d",*(a+i));
    printf(" ");
}
printf("\n(2)Decreasing:\n");
for(i=(n-1);i>=0;i--){
    printf("%d",*(a+i));
    printf(" ");
}
}
/************************************************/
if(method==2){
    divide(a,0,n-1);
    printf("mergesort:\n");
    printf("(1)Increasing:\n");
    for(i=0;i<n;i++){
        printf("%d",*(a+i));
        printf(" ");
    }
    printf("\n(2)Decreasing:\n");
    for(i=(n-1);i>=0;i--){
    printf("%d",*(a+i));
    printf(" ");
}
}
return 0;
}
