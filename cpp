#include <conio.h>
#include<string>
#include <iostream>
#include<stdlib.h>
#include <windows.h>
#include <stdlib.h>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_PLUS 43
#define ENTERR 80
#define TWO 79
#define ONE 88
COORD coord = {0, 0};
int matrix_dummy[4][4]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int matrix_dummy2[4][4]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int matrix[4][4]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int row,col;
int givescore(int[][4],int);
void predict(int[][4]);
void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void printall(int a[4][4])
{
    gotoxy(15,15);int i;int j;cout<<endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<a[i][j]<<"  ";
        }
        cout<<endl;
    }
}

void print_val(int a,int b){
    if(matrix[a][b]==1)cout<<"X";
    else if(matrix[a][b]==2)cout<<"O";
    else cout<<" ";
}
void putrandom()
{   int ended=0;
    while(ended==0)
    {
        int col1=rand()%4;int row1=rand()%4;
        if(matrix[row1][col1]==0){gotoxy(22+col1*6,3+row1*2);cout<<"X";matrix[row1][col1]=1;ended=1;row=row1;col=col1;}
    }
}
void copydummy2(int matrix1[4][4])
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            matrix_dummy2[i][j]=matrix1[i][j];
        }
    }
}

void copydummy(int matrix1[4][4])
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            matrix_dummy[i][j]=matrix1[i][j];
        }
    }
}

int first_step_do(int[][4],int);
int second_order(int[][4],int);
int main()
{
gotoxy(3,5);cout<<"Player O";gotoxy(60,5);cout<<"Player X";
gotoxy(4,6);cout<<"HUMAN";gotoxy(63,6);cout<<"AI";
gotoxy(3,7);cout<<"ScoreCard";gotoxy(60,7);cout<<"ScoreCard";
    //while(1){int c=getch();cout<<"  "<<c;}
   //for( int i=0;i<255;i++){cout<<i<<"  "<<(char)i<<endl;   }while(1);
int i=0;int turn=0;//zero means user input;
for(i=0;i<4;i++){
        gotoxy(19,3+i*2);cout<<"|";
        gotoxy(25,3+i*2);cout<<"|";
        gotoxy(31,3+i*2);cout<<"|";
        gotoxy(37,3+i*2);cout<<"|";
        gotoxy(43,3+i*2);cout<<"|";
}


 /*for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            gotoxy(22+i*6,3+j*2);cout<<"0";
        }
    }

*/
    int c = 0,space=0;

    gotoxy(22,3);cout<<"_";gotoxy(22,3);row=0;col=0;

    while(space==0)
    {
        gotoxy(4,8);cout<<givescore(matrix,2);gotoxy(63,8);cout<<givescore(matrix,1);
        gotoxy(22+col*6,3+row*2);
        c = 0;
        switch((c=getch()))
        {
        case KEY_LEFT:
        if(col==0)break;
        else {gotoxy(22+col*6,3+row*2);print_val(row,col);gotoxy(22+col*6,3+row*2);col--;}
        gotoxy(22+col*6,3+row*2);cout<<"_";gotoxy(22+col*6,3+row*2);

        break;

        case KEY_RIGHT:
        if(col==3)break;
        else {gotoxy(22+col*6,3+row*2);print_val(row,col);gotoxy(22+col*6,3+row*2);col++;}
        gotoxy(22+col*6,3+row*2);cout<<"_";gotoxy(22+col*6,3+row*2);
        break;

        case KEY_UP:
        if(row==0)break;
        else {gotoxy(22+col*6,3+row*2);print_val(row,col);gotoxy(22+col*6,3+row*2);row--;}
        gotoxy(22+col*6,3+row*2);cout<<"_";gotoxy(22+col*6,3+row*2);
        break;
        case KEY_DOWN:
        if(row==3)break;
        else {gotoxy(22+col*6,3+row*2);print_val(row,col);gotoxy(22+col*6,3+row*2);row++;}
        gotoxy(22+col*6,3+row*2);cout<<"_";gotoxy(22+col*6,3+row*2);
        break;
        //case ONE:
        //    if(matrix[row][col]==0){cout<<"X";matrix[row][col]=1;predict(matrix);}
        //    break;
        case TWO:
            if(matrix[row][col]==0){cout<<"O";matrix[row][col]=2;predict(matrix);}
            break;
        case KEY_PLUS:
            //gotoxy(20,20);cout<<givescore(matrix,1);
            predict(matrix);
            }
    }

   return 0;
}
int first_step_do(int a[4][4],int l)
{
    int changed=0;
    int initial_score=givescore(a,l);
    int testcase_score;
    int ended=0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            copydummy(a);

            if(matrix_dummy[i][j]==0)
                {
                matrix_dummy[i][j]=l;
                testcase_score=givescore(matrix_dummy,l);
                if(testcase_score>initial_score){gotoxy(22+j*6,3+i*2);cout<<"X";matrix[i][j]=1;changed=1;row=i;col=j;break;}
                matrix_dummy[i][j]=0;
                }
        }
        if(changed==1)break;
    }
    return changed;
}
void predict(int a5[4][4])
{
int block_result;
int result= first_step_do(a5,1);
if (result==0){block_result=first_step_do(a5,2);}



if(block_result==0)
{
int changed=0;
for(int i=0;i<4;i++)
{
    for(int j=0;j<4;j++)
    {
        copydummy(a5);


        if(matrix_dummy[i][j]==0)
        {
            matrix_dummy[i][j]=1;

            int second_result=second_order(matrix_dummy,1);
            if(second_result==1){gotoxy(22+j*6,3+i*2);cout<<"X";matrix[i][j]=1;changed=1;row=i;col=j;break;}
            matrix_dummy[i][j]=0;
        }
        if(changed==1)break;
    }
    if(changed==1)break;
}

if(changed==0)
{
    int changed=0;
for(int i=0;i<4;i++)
{
    for(int j=0;j<4;j++)
    {
        copydummy(a5);


        if(matrix_dummy[i][j]==0)
        {
            matrix_dummy[i][j]=2;

            int second_result=second_order(matrix_dummy,2);
            if(second_result==1){gotoxy(22+j*6,3+i*2);cout<<"X";matrix[i][j]=1;changed=1;row=i;col=j;break;}
            matrix_dummy[i][j]=0;
        }
        if(changed==1)break;
    }
    if(changed==1)break;
}
}

}


}

int second_order(int a2[4][4],int l)
{
    int testcase_score;
    int initial_score;
    initial_score=givescore(a2,l);
    int changed=0;
      for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            copydummy2(a2);
            if(matrix_dummy2[i][j]==0)
                {
                matrix_dummy2[i][j]=l;
                testcase_score=givescore(matrix_dummy2,l);

                if(testcase_score>initial_score){return 1;changed=1;}
                matrix_dummy2[i][j]=0;
                }
        }
        if(changed==1)break;
    }
    return changed;
}
int givescore(int a[4][4],int l)
{
int p=0;
int c=0;

for (int i=0;i<4;i++)
{
for (int j=0;j<4;j++)
{
if (a[i][j]==l)
c++;
else if(j!=3)
c=0;
}
if (c==3)
p++;
else if (c==4)
p+=2;

c=0;
}


for (int i=0;i<4;i++)
{
for (int j=0;j<4;j++)
{
if (a[j][i]==l)
c++;
else if(j!=3)
c=0;
}
if (c==3)
p++;
else if (c==4)
p+=2;

c=0;
}

for (int i=0;i<4;i++)
{
for (int j=0;j<4;j++)
{
if (i==j)
{
if (a[i][j]==l)
c++;
else if(j!=3)
c=0;
}}}
if (c==3)
p++;
else if (c==4)
p+=2;


c=0;
for (int i=0;i<4;i++)
{
for (int j=0;j<4;j++)
{
if (i+j==3)
{
if (a[i][j]==l)
c++;
else if(j!=3)
c=0;
}}}
if (c==3)
p++;
else if (c==4)
p+=2;


c=0;

return(p);
}

