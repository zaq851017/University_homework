#include<stdio.h>
#include<stdlib.h>
int main(){
int a=0,b=0,c,w=0,d=0,l=0;
printf("Please input the round you want to play:\n");
scanf("%d",&a);
for(;a>=1;a--)
{
printf("#Please threw the Fist you want, 1=scissors 2=stone 3=paper:");
scanf("%d",&b);
srand(time(NULL));
int c= rand() % 3;
if(c==0&&b==1)
     {
    printf("You threw scissors, Computer threw scissors, YOU DREW\n!!");
    d++;
    c=0;
    }
else if(c==0&&b==2)
    {
    printf("You threw stone, Computer threw scissors, YOU WIN\n!!");
    w++;
    c=0;
    }
else if(c==0&&b==3)
    {
        printf("You threw stone, Computer threw paper, YOU WIN\n!!");
        l++;
        c=0;
    }
else if(c==1&&b==1)
    {
    printf("You threw scissors, Computer threw stone,YOU LOSE\n!!");
    l++;
    c=0;
    }
else if(c==1&&b==2)
    {
    printf("You threw stone, Computer threw stone,YOU DREW\n!!");
    d++;
    c=0;
    }
    else if(c==1&&b==3)
    {
        printf("You threw paper, Computer threw stone,YOU LOSE\n!!");
        w++;
        c=0;
    }
    else if(c==2&&b==1)
    {
        printf("You threw scissors, Computer threw paper,YOU WIN\n!!");
        w++;
        c=0;
    }
    else if(c==2&&b==2)
    {
        printf("You threw stone, Computer threw paper,YOU LOSE\n!!");
        l++;
        c=0;
    }
    else if(c==2&&b==3)
    {
        printf("You threw stone, Computer threw paper,YOU DREW\n!!");
        d++;
        c=0;
    }

}
printf("WIN:%d\n",w);
printf("DREW:%d\n",d);
printf("LOSE:%d\n",l);
return 0;
}
