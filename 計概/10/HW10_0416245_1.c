#include<stdio.h>
#include<stdlib.h>
int main(){
int num,lim,i,j,temp;
int end=1;
int former,latter;//control matrix
for(;;){
scanf("%d %d",&num,&lim);
int  a[num],b[lim][2];
if(num==0&&lim==0) break;//end exit
for(i=0;i<num;i++) a[i]=i+1;//read number
for(i=0;i<lim;i++) scanf("%d %d",&b[i][0],&b[i][1]);
while(end){
end=0;//end exit
  for(i=0;i<lim;i++){
    for(j=0;a[j]!=b[i][0];j++); former=j;
    for(j=0;a[j]!=b[i][1];j++); latter=j;
    if(former>latter){
        temp=a[former];
        a[former]=a[latter];
        a[latter]=temp;
        end=1;//change need to recycle to find wrong
    }
  }
}
 for(i=0;i<num;i++){
    printf("%d",a[i]);
    printf(" ");
}
printf("\n");
end=1;//restart loop
}
return 0;
}
