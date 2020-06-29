#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW 12
#define COL 12
int a=0; //decide whether end.
/*******PRINT***********/
void printmap(char map[ROW][COL]){
int i=0,j=0;
for(i=0;i<ROW;i++){
for(j=0;j<COL;j++){
printf("%c",map[i][j]);
printf(" ");
}
printf("\n");
}
printf("\n");
}
/******Method***********/
void mazeTraverse(char *maze, int row, int col, int startRow,int startColumn)
{
    maze[12*row+col]='X';
    printmap(maze);
    if(col!=startColumn||row!=startRow){
        if(row==0||row==11||col==0||col==11){
        printf("SUCCESS!");
        printf("\n");
        a=1;
        return ;
            }
    }
    if((row+1)<12&&maze[12*(row+1)+col]=='.'){
    maze[12*(row+1)+col]='X';
    printmap(maze);
    system("pause");
    mazeTraverse(maze,row+1,col,startRow,startColumn);
    if(a==1) {return ;}
    }
    if((row-1)>=0&&maze[12*(row-1)+col]=='.'){
        maze[12*(row-1)+col]='X';
        printmap(maze);
        system("pause");
        mazeTraverse(maze,row-1,col,startRow,startColumn);
        if(a==1) {return ;}
    }
    if((col+1)<12&&maze[12*row+(col+1)]=='.'){
        maze[12*row+(col+1)]='X';
        printmap(maze);
        system("pause");
        mazeTraverse(maze,row,col+1,startRow,startColumn);
        if(a==1) {return ;}
    }
    if((col-1)>=0&&maze[12*row+(col-1)]=='.'){
        maze[12*row+(col-1)]='X';
        printmap(maze);
        system("pause");
        mazeTraverse(maze,row,col-1,startRow,startColumn);
        if(a==1) {return ;}
    }
}

/******Generate*********/
void mazegenerate(char *maze){
int i,j,dir;
for(i=0;i<12;i++){
    for(j=0;j<12;j++){
    maze[(12*i)+j]='#';
    }
}
int startloc1=rand()%4;//decide where start
int startloc2=rand()%10+1;//point is not suitable
int startrow,startcol,row,col;
switch(startloc1){
case 0:startrow=0,startcol=startloc2,row=startrow,col=startcol;
       maze[12*row+col]='X';
       row++;
       maze[12*row+col]='.';
       break;
    // go down
case 1:startcol=0,startrow=startloc2,row=startrow,col=startcol;
       maze[12*row+col]='X';
       col++;
       maze[12*row+col]='.';
       break;
       //go right
case 2:startrow=11,startcol=startloc2,row=startrow,col=startcol;
       maze[12*row+col]='X';
       row--;
       maze[12*row+col]='.';
       break;
case 3:startcol=11,startrow=startloc2,row=startrow,col=startcol;
       maze[12*row+col]='X';
       col--;
       maze[12*row+col]='.';
       break;
}
while(row!=0&&row!=11&&col!=0&&col!=11){
    dir=rand()%4;
    switch(dir){

    case 0:if(row+2<ROW){
    row=row+2;
    maze[12*row+col]='.';
    maze[12*(row-1)+col]='.';
    }
    break;

    case 1:if(row-2>=0){
    row=row-2;
    maze[12*row+col]='.';
    maze[12*(row+1)+col]='.';
    }
    break;

    case 2:if(col+2<COL){
    col=col+2;
    maze[12*row+col]='.';
    maze[12*row+(col-1)]='.';
    }
    break;

    case 3:if(col-2>=0){
    col=col-2;
    maze[12*row+col]='.';
    maze[12*row+(col+1)]='.';
    }
    break;
    }
}
mazeTraverse(maze,startrow,startcol,startrow,startcol);
}
/******Main Function****/
int main(){
char map[ROW][COL]={'#','#','#','#','#','#','#','#','#','#','#','#',
                 '#','.','.','.','#','.','.','.','.','.','.','#',
                 '.','.','#','.','#','.','#','#','#','#','.','#',
                 '#','#','#','.','#','.','.','.','.','#','.','#',
                 '#','.','.','.','.','#','#','#','.','#','.','.',
                 '#','#','#','#','.','#','.','#','.','#','.','#',
                 '#','.','.','#','.','#','.','#','.','#','.','#',
                 '#','#','.','#','.','#','.','#','.','#','.','#',
                 '#','.','.','.','.','.','.','.','.','#','.','#',
                 '#','#','#','#','#','#','.','#','#','#','.','#',
                 '#','.','.','.','.','.','.','#','.','.','.','#',
                 '#','#','#','#','#','#','#','#','#','#','#','#',};
int startRow=2,startColumn=0;
mazeTraverse(map,startRow,startColumn,startRow,startColumn);
a=0;
system("pause");
mazegenerate(map);
return 0;
       }
