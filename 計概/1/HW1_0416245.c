#include<stdio.h>
int main(){
int num,a,b,c,d,e;
printf("Enter a 5-digit integer:");
scanf("%d",&num);
a=num/10000;
b=(num-a*10000)/1000;
c=(num-a*10000-b*1000)/100;
d=(num-a*10000-b*1000-c*100)/10;
e=(num-a*10000-b*1000-c*100-d*10)/1;
if(a<1||a>=10)
printf("Your input is not a 5-digit integer. Exit");
else{
if(a==e&&b==d)
printf("It is a palindrome.");
else
printf("It is not a palindrome");
}
return 0;
}
