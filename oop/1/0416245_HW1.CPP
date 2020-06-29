#include<iostream>
#include<string.h>
#include<cstdlib>
using namespace std;
void ADD(int [],int [],int []);
void SUB(int [],int [],int []);
void MUL(int [],int [],int []);
void DIV(int [],int ,int []);
void Print(int []);
void SmallMul(int [], int, int []);
bool CompareLarge(int [], int []);
int main(){
	char a[256]={0},b[256]={0};
	char A[256]={0},B[256]={0};
	int C[256]={0},D[256]={0},ANS[256]={0};
	int temp=0,j=0;
	int la=0,lb=0;
	char sign;
	cout<<"Input a number: ";
	cin>>a;
	la=strlen(a);
	cout<<"Input a sign: ";
	cin>>sign;
	cout<<"Input a number: ";
	cin>>b;
	lb=strlen(b);
	for(int i=la-1;i>=0;i--){
		temp=a[i];
		A[j]=temp;
		j++;
	}
	j=0;
	for(int i=lb-1;i>=0;i--){
		temp=b[i];
		B[j]=temp;
		j++;
	}
	j=0;
	for(int i=0;i<la;i++){
		C[i]=A[i]-'0';
	}
	for(int i=0;i<lb;i++){
		D[i]=B[i]-'0';
	}
	unsigned long int d=0;
	float l=0.1;
	for(int i=0;i<lb;i++){
            d=d+D[i]*10*l;
            l=l*10;
	}
	if(sign=='+'){
	ADD(C,D,ANS);}
	else if(sign=='-'){
	SUB(C,D,ANS);
	}
	else if(sign=='*'){
	MUL(C,D,ANS);
	}
	else if(sign=='/'){
	DIV(C,d,ANS);
	}
	return 0;
}

void Print(int A[]){
	cout<<"Result: ";
	int i=256-1;
	while (i >= 0 && A[i] == 0) i--;
	if (i < 0){
    cout << '0';}
    else{
    while (i >= 0) cout << A[i--];
	}
}

bool CompareLarge(int A[], int B[])
{
    for (int i=256-1; i>=0; i--)
        if (A[i] != B[i])
            return A[i] > B[i];
    return false;
}


void ADD(int A[], int B[], int C[])
{
    for (int i=0; i<256; i++)
        C[i] = A[i] + B[i];
    for (int i=0; i<255; i++)
    {
        C[i+1] += C[i]/10;
        C[i] %= 10;
    }
    Print(C);
}

void SUB(int A[], int B[], int C[])
{
    for (int i=0; i<256; i++)
        C[i] = A[i] - B[i];

    for (int i=0; i<255; i++)
        if (C[i] < 0)
        {
            C[i+1]--;
            C[i] += 10;
        }
        Print(C);
}

void MUL(int A[], int B[], int C[])
{
    for (int i=0; i<256; i++)
        C[i] = 0;

    for (int i=0; i<256; i++)
        for (int j=0; j<256; j++)
            if ((i+j)< 256)
                C[i+j] += A[i] * B[j];

    for (int i=0; i<256-1; i++)
    {
        C[i+1] += C[i] / 10;
        C[i] %= 10;
    }
       Print(C);
}

void SmallMul(int A[], int B, int C[])
{
    for (int i=0; i<256; i++)
        C[i] = A[i] * B;

    for (int i=0; i<256-1; i++)
    {
        C[i+1] += C[i] / 10;
        C[i] %= 10;
    }
}

void DIV(int A[], int B, int C[])
{
    int r = 0;
    for (int i=256-1; i>=0; i--)
    {
        r = r * 10 + A[i];
        C[i] = r / B;
        r %= B;
    }
    Print(C);
}
