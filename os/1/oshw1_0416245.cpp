#include<iostream>
#include<string.h>
#include<stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include<unistd.h>
#include<stdlib.h> 
#include <fcntl.h>
#include <cstring>
using namespace std;
int main()
{
	char command[200];
	//cout<<">";
	while(1)
	{
		cout<<"> ";
		cin.getline(command,200);
		if(command[0]=='e' && command[1]=='x' && command[2]=='i' && command[3]=='t')
			break;
		int wait1=0;
		int i=0;
		int redir0=0;
		int redir1=0;
		
		if(command[strlen(command)-1]=='&')
			wait1=1;
		for(int i=0;i<strlen(command);i++)
		{
			if(command[i]=='>')
				redir0=1;
			if(command[i]=='<')
				redir1=1;
		}
		char *pch=strtok(command," &");
		char *first=pch;
		char *second[100];
	
		//cout<<redir0;
			
		//cout<<pch<<first;
		while(pch!= NULL)
		{
			second[i]=pch;
			//cout<<second[i];
			i=i+1;
			pch=strtok(NULL," &><");
		}
			second[i]=NULL;
			char *output;
			output=second[i-1];
		char *third[100];
		for(int j=0;j<(i-1);j++)
		{
			third[j]=second[j];
		}
		third[i-1]=NULL;
		
		/*for(int j=0;j<(i-1);j++)
		{
			cout<<second[j]<<" ";
		}*/ 
		
		//	cout<<second[i-1]<<"\n";
		pid_t pid;
		pid=fork();
		if(pid<0){
			cout<<"Pid Fork Failed."<<endl;
			exit(-1);
		}
		else if(pid==0){ //child process
		
			if(redir0==1){
				int fd1 = creat(output , 0644) ;
				dup2(fd1, STDOUT_FILENO);
				close(fd1);
				execvp(first,third);
				exit(0);
			}
			
			else if(redir1==1){
				int fd0 = open(output,O_RDONLY) ;
				dup2(fd0, STDIN_FILENO);
				close(fd0);
				execvp(first,third);
				exit(0);
			}
			
			else if(wait1 ==0){ //no &
				execvp(first,second);
				exit(0);
			}
			else if(wait1 ==1){
				/*pid_t grand_pid;
				grand_pid=fork();*/
				pid=fork();
				if(pid<0){
					cout<<"Grand_pid Fork Failed."<<endl;
					exit(-1);
				}
				else if(pid>0){ //no use
					exit(0);
				}
				else if(pid ==0){
					execvp(first,second);
					cout<<"Execvp Error."<<endl;
					exit(0);
				}
				
			}
			
		}
		else if(pid > 0){
			waitpid (pid, NULL, 0); //parent process
			if(wait1 ==0){ //no &
				wait(NULL);
			}
			else{
				cout<<"[in process] "<<pid<<endl;
			}
		}
		//	waitpid (pid, NULL, 0);	
	}
	
	
	
	return 0;
 } 
