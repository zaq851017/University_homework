#include<stdio.h>
int main(){
int N,i=1,n=2,sum=0,a=0,b=0,c=0;
printf("Please input N:");
scanf("%d",&N);
for(n=2;n<=N;n++)
{
    for(i=1;i<n;i++)
    {
        if(n%i==0)
       {
            sum+=i;
       }
    }
    if(sum<n)
    a+=1;
    else if(sum==n)
    b+=1;
    else if(sum>n)
    c+=1;
    sum=0;

}
printf("DEFICIENT:%d\n",a);
printf("PERFECT:%d\n",b);
printf("ABUNDANT:%d",c);
return 0;

}
