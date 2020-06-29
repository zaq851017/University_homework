#include<stdio.h>
#include<stdlib.h>
#include<time.h>
    void q0(void){
    switch(getchar()) {
    case '+': q0(); return;
    case '-': q0(); return;
    case '1': q1(); return;
    case '2': q1(); return;
    case '3': q1(); return;
    case '4': q1(); return;
    case '5': q1(); return;
    case '6': q1(); return;
    case '7': q1(); return;
    case '8': q1(); return;
    case '9': q1(); return;
    case '0': q1(); return;
    case '.': q2(); return;
    case '\n': printf("Rejected  by Method 1\n"); return;
    }
 }
void q1(void)
{
    switch(getchar()) {
    case '+': q3(); return;
    case '-': q3(); return;
    case '1': q1(); return;
    case '2': q1(); return;
    case '3': q1(); return;
    case '4': q1(); return;
    case '5': q1(); return;
    case '6': q1(); return;
    case '7': q1(); return;
    case '8': q1(); return;
    case '9': q1(); return;
    case '0': q1(); return;
    case '.': q4(); return;
    case '\n': printf("Rejected  by Method 1\n"); return;
    }
}
void q2(void)
{
    switch(getchar()) {
    case '+': q3(); return;
    case '-': q3(); return;
    case '.': q3(); return;
    case '1': q4(); return;
    case '2': q4(); return;
    case '3': q4(); return;
    case '4': q4(); return;
    case '5': q4(); return;
    case '6': q4(); return;
    case '7': q4(); return;
    case '8': q4(); return;
    case '9': q4(); return;
    case '0': q4(); return;
    case '\n': printf("Rejected  by Method 1\n"); return;
    }
}

void q3(void)
{
    switch(getchar()) {
case '+':q3(); return;
case '-': q3(); return;
case '0': q3(); return;
case '1': q3(); return;
case '2': q3(); return;
case '3': q3(); return;
case '4': q3(); return;
case '5': q3(); return;
case '6': q3(); return;
case '7': q3(); return;
case '8':q3(); return;
case '9': q3(); return;
case '.': q3(); return;void recogniser1();
case '\n': printf("Rejected  by Method 1\n"); return;
    }
}
void q4(void)
{
    switch(getchar()) {
    case '+': q3(); return;
    case '-': q3(); return;
    case '.': q3(); return;
    case '1': q4(); return;
    case '2': q4(); return;
    case '3': q4(); return;
    case '4': q4(); return;
    case '5': q4(); return;
    case '6': q4(); return;
    case '7': q4(); return;
    case '8': q4(); return;
    case '9': q4(); return;
    case '0': q4(); return;
    case '\n': printf("Accepted  by Method 1\n"); return;
    }
}

void recogniser2(void){
 const sign=0,inte=1,frac=2,err=3,real=4;
 int ch;
 int go=sign;
while((ch=getchar()) != '\n')
 {
     if(go==sign){
        switch(ch){
        case'+':go=0;break;
        case'-':go=0;break;
        case'.':go=2;break;
        case'0':go=1;break;
        case'1':go=1;break;
        case'2':go=1;break;
        case'3':go=1;break;
        case'4':go=1;break;
        case'5':go=1;break;
        case'6':go=1;break;
        case'7':go=1;break;
        case'8':go=1;break;
        case'9':go=1;break;
        }
        continue ;
     }
     else if(go==inte){
        switch(ch){
        case'0':go=1;break;
        case'1':go=1;break;
        case'2':go=1;break;
        case'3':go=1;break;
        case'4':go=1;break;
        case'5':go=1;break;
        case'6':go=1;break;
        case'7':go=1;break;
        case'8':go=1;break;
        case'9':go=1;break;
        case'+':go=3;break;
        case'-':go=3;break;
        case'.':go=4;break;
        }
        continue;
     }

 else if(go==frac){
    switch(ch){
    case'0':go=4;break;
    case'1':go=4;break;
    case'2':go=4;break;
    case'3':go=4;break;
    case'4':go=4;break;
    case'5':go=4;break;
    case'6':go=4;break;
    case'7':go=4;break;
    case'8':go=4;break;
    case'9':go=4;break;
    case'+':go=3;break;
    case'-':go=3;break;
    case'.':go=3;break;
    }
    continue;
     }
     else if(go==err){
        switch(ch){
        case'.':go=3;break;
        case'0':go=3;break;
        case'1':go=3;break;
        case'2':go=3;break;
        case'3':go=3;break;
        case'4':go=3;break;
        case'5':go=3;break;
        case'6':go=3;break;
        case'7':go=3;break;
        case'8':go=3;break;
        case'9':go=3;break;
        case'+':go=3;break;
        case'-':go=3;break;
        }
        continue;
     }
     else if(go==real){
        switch(ch){
       case'0':go=4;break;
    case'1':go=4;break;
    case'2':go=4;break;
    case'3':go=4;break;
    case'4':go=4;break;
    case'5':go=4;break;
    case'6':go=4;break;
    case'7':go=4;break;
    case'8':go=4;break;
    case'9':go=4;break;
    case'.':go=3;break;
    case'+':go=3;break;
    case'-':go=3;break;
        }
        continue;
     }

 }
 if(go==real) printf("Accepted by method 2\n");
 else printf("Rejected by method 2\n");
}


int main(void)
{    srand(time(NULL));
    printf("Enter a real number:");
    int ch;
    while((ch=getchar()) != EOF) {
        ungetc(ch, stdin);
        int m = rand()% 2+1;
        switch(m) {
            case 1: q0();
                break;
            case 2: recogniser2();
                break;
        }
    }
    return 0;
}
