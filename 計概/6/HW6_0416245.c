#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int  main(){
char a[100],b[100],change;
int la,lb,k,digit=0,i,l;
int c[100],d[100],sum[100],sub[100],mul[100][100]={0},mul_sum[102]={0};

printf("Input a:");
gets(a);
la=strlen(a);
printf("Input b:");
gets(b);
lb=strlen(b);


for(k=la;k<100;k++) a[k]='0';
for(k=lb;k<100;k++) b[k]='0';


for(k=0;k<(la/2);k++){
    change=a[k];
    a[k]=a[la-k-1];
    a[la-k-1]=change;
}

for(k=0;k<(lb/2);k++){
    change=b[k];
    b[k]=b[lb-k-1];
    b[lb-k-1]=change;
}




for(i=0;i<100;i++){
    c[i]=(int)a[i]-48;
}

for(i=0;i<100;i++){
    d[i]=(int)b[i]-48;
}
/****************************************************************************/
//+
for(k=0;k<la-1;k++){
    sum[k]=c[k]+d[k]+digit;
    if(c[k]+d[k]+digit>=10){
        sum[k]=c[k]+d[k]+digit-10;
        digit = 1;
    }
    else {
        sum[k]=c[k]+d[k]+digit;
        digit = 0;
    }

}

if(c[la-1]+d[la-1]+digit>=10){
    sum[la-1]=c[la-1]+d[la-1]+digit-10;
    sum[la]=1;
    la=la+1;
}
else sum[la-1]=c[la-1]+d[la-1]+digit;
printf("a+b=");
for(i=la-1;i>=0;i--){
    printf("%d",sum[i]);
}
printf("\n");
/******************************************************************************/
//-
k=0;
printf("a-b=");
for(i=0;i<la;i++){
    if(a[i]-b[i]>=0){
        sub[i]=a[i]-b[i];
        k=0;
    }
    else {
        sub[i]=a[i]-b[i]+10;
        k=1;
    }
    if(k==1){
        a[i+1]=a[i+1]-1;
    }
}
 while(sub[la-1]==0)
    {
        la=la-1;
    }
    if(la<0){
        printf("0");
    }
for(k=la-1;k>=0;k--){
    printf("%d",sub[k]);
}
printf("\n");
/********************************************************************************/
printf("a*b=");
for(k=0;k<100;k++){
    for(l=0;l<100;l++){
        mul[l][k]=c[l]*d[k];
    }
}
k=0;
while(k<100){
    l=0;
    while(k>=l){
        mul_sum[k]=mul_sum[k]+mul[l][k-l];
        l++;
    }
    k++;
}
k=0;
while(k<102){
        if(mul_sum[k]>=10){
             mul_sum[k+1]+=(mul_sum[k]/10);
             mul_sum[k]%=10;
        }
        k++;
}
k=101;
while(mul_sum[k]==0)
    {
        k--;
    }
    if(k<0){
        printf("0");
    }
    while(k>=0)
    {
        printf("%d",mul_sum[k]);
        k--;
    }
return 0;
}
