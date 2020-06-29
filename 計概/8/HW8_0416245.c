#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW 12
#define COL 22
/********************************/
void init_map(char map[ROW][COL]){
int i,j;
for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++){
        map[i][j]='1';
    }
}
for(i=1;i<=10;i++){
    for(j=1;j<=20;j++){
        map[i][j]='#';
    }
}
}
/*******************************/
int findmother(int a,int b,int x,int y,char m[ROW][COL]){
if(x<=10&&y<=20){
if(m[x-1][y]=='#'||m[x+1][y]=='#'||m[x][y+1]=='#'||m[x][y-1]=='#'){
if(m[x-1][y]=='#'){
    m[x-1][y]='z';
}
if(m[x+1][y]=='#'){
    m[x+1][y]='z';
}
if(m[x][y+1]=='#'){
    m[x][y+1]='z';
}
if(m[x][y-1]=='#'){
    m[x][y-1]='z';
}
findmother(a,b,x-1,y,m);
findmother(a,b,x+1,y,m);
findmother(a,b,x,y-1,m);
findmother(a,b,x,y+1,m);
}
}

if(m[a-1][b]=='z'||m[a+1][b]=='z'||m[a][b+1]=='z'||m[a][b-1]=='z'){
    return 1;
}
}
/*******************************/
int main(void){
char map[ROW][COL];
srand(time(NULL));
int i,j;
int x,y;
int dir;
int ch=65;//'A'
int a,b,result=0;
init_map(map);
x=rand()%10+1;
y=rand()%20+1;
map[x][y]=ch;
a=x,b=y;
for(ch=66;ch<=90;ch++){
    dir = rand()%4;
    switch(dir){
    case 0: {if(x-1>=1&&map[x-1][y]=='#') {--x;map[x][y]=ch;}
             else ch--;}
    break;//up
    case 1: {if(x+1<=10&&map[x+1][y]=='#'){++x;map[x][y]=ch;}
             else  ch--;}
    break; //down
    case 2: {if(y+1<=20&&map[x][y+1]=='#'){++y;map[x][y]=ch;}
             else  ch--;}
    break; //right
    case 3:{if(y-1>=1&&map[x][y-1]=='#') {--y;map[x][y]=ch;}
            else  ch--;}
    break;//left
    }
    if(map[x-1][y]!='#'&&map[x+1][y]!='#'&&map[x][y-1]!='#'&&map[x][y+1]!='#'){
        ch=91;//end
    }
}
for(i=1;i<=10;i++){
    for(j=1;j<=20;j++){
        printf("%c",map[i][j]);
    }
    printf("\n");
}
result=findmother(a,b,x,y,map);
if(result==1){
    printf("YES");
}
else {
    printf("NO");
}
return 0;
}
