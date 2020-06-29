#include<stdio.h> 
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
int main(int argc , char **argv)
{
	ifstream infile(argv[1]);
	//ifstream infile("input.txt");
	char input[1000];
	infile.getline(input,1000);
	int  in_length = strlen(input);
	//cout<<in_length ;
	
	cout<<"reverse ";
	for(int i=0;i<in_length;i++)
		cout<<input[i];
	cout<<"\n";
	for(int i=in_length-1;i>=0;i--)
	{
		cout<<input[i];
	}
	cout<<"\n";
	cout<<"split ";
	for(int i=0 ;i<in_length;i++)
		cout<<input[i];
	cout<<"\n";
	char *ch=argv[2];
	//cout<<strlen(ch);
	int x=0;
	int y=0;
for(int i=0;i<in_length;i++)
{
	x=i;
	for(int j=0;j<=strlen(ch);j++)
	{
		if(j == strlen(ch)) //match
		{
			i=i+strlen(ch)-1;
			if(y==0)break;
			else
			{
			cout<<" ";
			break;
			}
			
		}
		if(input[x] != ch[j])
		{
			cout<<input[i];
			y=1;
			break;
		}
		x=x+1;
	}
	
	
}
	x=0;
	y=0;
	
	
	
	cout<<"\n";  // input.text  finish
	
	char input2[1000];
	cin.getline(input2,1000);
	char *title1=strtok(input2," ");
	char *main_input=strtok(NULL,"");
	//cout<<title1;
	//cout<<title2;
	//cout<<main_input;
	while(title1[0]!='e' && title1[1] != 'x' && title1[2] != 'i' && title1[3] != 't')
	{
		char input3[1000];
		in_length=strlen(main_input);
		if(title1[0] =='r')
		{
			for(int i=strlen(main_input)-1;i>=0;i--)
				cout<<main_input[i];
			cout<<"\n";
		}

		else if(title1[0] =='s')
		{
			for(int i=0;i<in_length;i++)
		{
		x=i;
		for(int j=0;j<=strlen(ch);j++)
		{
		if(j == strlen(ch)) //match
		{
			i=i+strlen(ch)-1;
			if(y==0)break;
			else
			{
			cout<<" ";
			break;
			}
			
		}
		if(main_input[x] != ch[j])
		{
			cout<<main_input[i];
			y=1;
			break;
		}
		x=x+1;
	}
	
	}
			cout<<"\n";
		}
		cin.getline(input3,1000);
		title1=strtok(input3," ");
		main_input=strtok(NULL,"");
		x=0;
		y=0;
		
	}
	
	
	return 0;
}
