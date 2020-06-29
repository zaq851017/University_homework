#include<stdio.h>
#include<stdlib.h>
int substract(int a,int b){
int M;
M=a-b;
return M;
}
int main(){
int A[64],F=0,E=0,i=0,n=0,R=0,D[10]={0},m,V=0;
char c;
printf("Input a name :");
while( ( c=getchar() ) != '\n')
{
A[i]=(int)c;
i++;
}
n=(i-1);
for(i=0;i<n;i++){
    F+=A[i]+A[i+1];
}
for(i=0;i<n;i++){
    E+=A[i+1]-A[i];
}
R=substract(F,E);
if(F-E<0){
    R=R*(-1);
}
V=R;
while(R != 0){
    m=R%10;
    D[m]=1;
    R/=10;
}
if(D[1]==1||D[0]==1||D[8]==1){
    if(D[2]==1||D[3]==1||D[4]==1||D[5]==1||D[6]==1||D[7]==1||D[9]==1){
        printf("Common,%d",V);
    }
    else {
        printf("Wonderful,%d",V);
    }
}
else printf("Ugly,%d",V);
return 0;
}
