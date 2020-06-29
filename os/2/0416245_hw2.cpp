#include<iostream>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/time.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int main(){
	int dim=0;
	int dig=0;
	cout<<"Input the matrix dimension: ";
	cin>>dim;
	cout<<"\n";
	int shmid1=shmget(0,4*dim*dim,IPC_CREAT | 0600) ; //IPC_CREAT | 0600   for read only shm
	int shmid2=shmget(0,4*dim*dim,IPC_CREAT | 0600) ;
	unsigned int *matrix=(unsigned int *)shmat(shmid1,NULL,0);
	
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			matrix[i*dim+j]=dig;
			dig = dig+1;
		}
	}
	//cout<<"COMPLETE.";
	unsigned int *matrix_add=(unsigned int *)shmat(shmid2,NULL,0);
	int matrix_start=0;
	int matrix_end=dim/1;
	int pre_matrix_end=0;
	unsigned int checksum=0;
	double sec=0.0;
	double u_sec=0.0;
	
	//mulitiple process 
	for(int i=1;i<=16;i++){
		struct timeval start,end;
		gettimeofday(&start, 0);
			matrix_start=0;
			matrix_end=dim/i;
			pre_matrix_end=0;
		cout<<"Multiplying matrices using "<<i<<" process\n";
		for(int j=1;j<=i;j++){ //process multiplication
			matrix_start=pre_matrix_end;
			if(j==i)
			{
				matrix_end=dim;
			}
			else
			{
				matrix_end=matrix_start+(dim/i);
			}
			pre_matrix_end=matrix_end;
			pid_t pid=fork();
			if(pid <0){
				cout<<"Pid Fork Failed."<<endl;
				exit(-1);
			}
			else if(pid ==0){
				matrix_add=(unsigned int *) shmat(shmid2,NULL,0);
				matrix =(unsigned int *)shmat(shmid1,NULL,0);
				
				for(int m=matrix_start;m<matrix_end;m++){
					for(int n=0;n<dim;n++){
						matrix_add[n+m*dim]=0;
						for(int p=0;p<dim;p++)
						{
							matrix_add[n+m*dim]=matrix_add[n+m*dim]+(matrix[m*dim+p]*matrix[p*dim+n]);
						}
					}
				}
				shmdt(matrix);
				shmdt(matrix_add) ;
				exit(0);
			}
			else if(pid >0){//parent process
				
			}
				
		}
		
		for(int k=0;k<i;k++)
			 wait(NULL);
		gettimeofday(&end,0);
		sec=(end.tv_sec-start.tv_sec);
		u_sec=(end.tv_usec-start.tv_usec);
		cout<<"Elapsed time: "<<sec+(u_sec/(1000000.0))<<"sec,"<<"Checksum: ";
		for(int x=0;x<dim;x++)
		{
			for(int y=0;y<dim;y++)
				checksum=checksum+matrix_add[x*dim+y];
		}
		cout<<checksum<<"\n";
		checksum=0;
	}
	shmctl(shmid1, IPC_RMID, NULL) ;
	shmctl(shmid2, IPC_RMID, NULL) ;
	return 0;

} 
