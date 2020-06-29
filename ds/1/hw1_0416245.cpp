#include<iostream>
#include<fstream>
using namespace std;
int *failure=new int [1000000];
int a=0;
int count=0;
int pos=0;
void fail_func(char *key)
{
	failure[0]=-1;
	for(int i=1,j=-1;key[i]!='\0'; i++)
	{
		 while (j >= 0 && key[j+1] != key[i])
            j = failure[j];
        if (key[j+1] == key[i]) j++;
        failure[i] = j;	
	}
}
void function(char *t,char *p,int *position,int keysize)
{
	fail_func(p);
	for(int i=0,j=-1;t[i]!='\0';i++)
	{
		while (j >= 0 && p[j+1] != t[i])
            j = failure[j];
		if (p[j+1] == t[i]) 
		j++;
		if(i!=0&&(t[i] == '\n' || t[i] == ',' || t[i] == '.' || t[i] == '?' || t[i] == '!'||t[i]==';'||t[i] ==':'||t[i]-1==']'||t[i]=='}')&&t[i+1]!='\0') 
		pos++; 
		if(j==keysize-1)
		{
			if((i==j||t[i-j-1] == '\n' || t[i-j-1] == ',' || t[i-j-1] == '.' || t[i-j-1] == '?' || t[i-j-1] == '!'||t[i-j-1]==';'||t[i-j-1] ==':'||t[i-j]-1==']'||t[i-j-1]=='}')&&(t[i+1]==0||t[i+1] == '\n' || t[i+1] == ',' || t[i+1] == '.' || t[i+1] == '?' || t[i+1] == '!'|| t[i+1]==';'||t[i+1] ==':'||t[i+1]==']'||t[i+1]=='}'))
			count++;
			position[a]=pos;
			j=failure[j];
			a++;
			
		}	
	}
}
int main()
{
int keysize=0;
char *str=new char[1000000];
int  *position=new int[1000000];
char *key=new char[1000000];
char text[2][100];
cin>>text[0];
cin>>text[1];
fstream fin,fout;
fin.open(text[0],ios::in);
fout.open(text[1],ios::out);
if(!fin||!fout)
 	printf("The File opens fail\n");
else
{
	while (fin >> str) 
	{
		if(pos==0)
		{
			for(int i=0;str[i]!=0;i++)
			{
				key[i]=str[i];
				keysize++;
			}	
		}
	pos++;
	function(str,key,position,keysize);
	}

	fout<<count<<endl;
	for(int j=0;position[j]!=0;j++)
		fout<<position[j];
		
	fin.close(); 
	fout.close();  
}

return 0; 

}
 
