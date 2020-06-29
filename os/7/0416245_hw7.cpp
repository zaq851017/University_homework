#include<iostream>
#include<string.h>
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
using namespace std;
int main(int argc,char **argv){
	struct timeval start , end ;
	//start 
	if(argc!=2)
		cout<<"Please Key the dick position.\n";
	gettimeofday(&start,0) ;
	char garbage_buff[1024]={0};
	// one file is 64KB
	for(int i=0;i<1280;i++){
		char file_name[60];
		sprintf(file_name,"%s/%d.txt",argv[1],i) ;
		FILE *file = fopen(file_name,"w");
		for(int i=0;i<64;i++){
			fwrite(garbage_buff,1,sizeof(garbage_buff),file);
		}
		fclose(file);
	}
	// delete file
	for(int i=1;i<1280;i=i+2){
		char file_name[60];
		sprintf(file_name,"%s/%d.txt",argv[1],i) ;
		remove(file_name);
	}
	// write large_file.txt into disk
	char large_name[60];
	sprintf(large_name,"%s/largefile.txt",argv[1]);
	FILE *large_file= fopen(large_name,"w");
	for(int i=0;i<64*700;i++){
		fwrite(garbage_buff , 1 , sizeof(garbage_buff) , large_file ) ;
	}
	for(int i=0;i<1280;i=i+2){
		char file_name[60];
		sprintf(file_name,"%s/%d.txt",argv[1],i) ;
		remove(file_name);
	}
	char cmd[100];
	sprintf(cmd,"filefrag -v %s/largefile.txt",argv[1]);
	system("sync");
	system(cmd);
	gettimeofday(&end ,0) ;
	cout<<"Elapsed time in : "<<end.tv_sec - start.tv_sec + ( end.tv_usec - start.tv_usec)/1000000.0 <<" seconds\n";
	fclose(large_file);
	


}
