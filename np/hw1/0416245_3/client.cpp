#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include<iostream>
#include <sys/select.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;
int main(int argc,char **argv){  //argv[1] =server IP,argv[2]=server port


int c_sockfd;
struct sockaddr_in servaddr ;  

if(argc !=3){
	cout<<"User do not key in IP and Port.\n";
	return 0;
}

if( (c_sockfd = socket( AF_INET,SOCK_STREAM,0)) <0 ){
	cout<<"Socket error.\n";
	return 0;
}


bzero( &servaddr , sizeof(servaddr) );
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons ( atoi(argv[2] ) ) ;
inet_pton ( AF_INET,argv[1],&servaddr.sin_addr );

if( (connect ( c_sockfd,(struct sockaddr *) & servaddr , sizeof(servaddr) ) )<0 ){
	cout<<"connect error.\n";
	return 0;
}

int numfds ;
fd_set rset;
FD_ZERO (&rset);
char send_buff[1000];
char rec_buff[1000] ;

while (1) {
	
	FD_SET ( c_sockfd , &rset) ;//將連上server的socket丟進rset裡面
	FD_SET ( fileno(stdin) , &rset) ;//將stdin丟到rset裡面
	
	numfds = max(fileno(stdin), c_sockfd ) + 1;
	select (numfds , &rset , NULL,NULL,NULL );
	
	int read_len ;
	
	if(FD_ISSET (c_sockfd ,&rset ) ) //c_sockfd is readable
	{
		if( (read_len = read( c_sockfd ,rec_buff,1000 ) ) == 0){
			close (c_sockfd);
			return 0;
		}
		rec_buff[read_len] = 0;
		cout<<rec_buff <<"\n";
		
	}
	
	if( FD_ISSET (fileno(stdin), &rset )  ) // stdin is readable 
	{
		if( fgets(send_buff ,1000,stdin) == NULL ){
			close(c_sockfd);
			return 0;
		}
		if( send_buff [0] == 'e' && send_buff[1] =='x' && send_buff[2]=='i' && send_buff[3]=='t'){
			close(c_sockfd);
			return 0;
		}
		write (c_sockfd,send_buff,strlen(send_buff) );
		
	}
	
	
}

return 0;
}
