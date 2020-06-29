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
using namespace std;
char c_name [100][50] ;  //100 client , 50 name_word
char c_ip   [100][50];  // client_ip
unsigned int c_port[100] ;
bool is_name[100]={false};

void hello (int c[100] , int rec,struct sockaddr_in *c_addr,int maxi ){
	char buffer[1000];
	c_port [rec] = ntohs(c_addr->sin_port);
	inet_ntop(AF_INET,&c_addr->sin_addr,c_ip[rec],sizeof(c_ip[rec])); //將client ip丟進去c_ip裡面
	if(is_name[rec] == false) //user is anoymous
	{
		sprintf( buffer ,"[Server] Hello, anoymous! From %s/%hu\n",c_ip[rec],c_port[rec] );
		write(c[rec],buffer,strlen(buffer));
		strcpy(c_name[rec] ,"anoymous");
		
		for(int i=0;i<=maxi;i++){
			if(i == rec){
				continue;
			}
			else{
				sprintf(buffer,"[Server] Someone is coming!\n");
				write(c[i] ,buffer , strlen(buffer));
			}
			
		}
		
	}
	else{ //user has name
		sprintf(buffer,"[Server] Hello,%s! From: %s/%hu\n",c_name[rec],c_ip[rec],c_port[rec] );
		write(c[rec] , buffer ,strlen(buffer) );
		for(int i=0;i<=maxi;i++){
			if(i == rec){
				continue;
			}
			else{
				sprintf(buffer,"[Server] Someone is coming!\n");
				write(c[i] ,buffer , strlen(buffer));
			}
			
		}
		
		
	}
	 
}


void command (int c_socket[100] ,int maxi,int rec,char recv_line[1000]){
	int counter =0 ;
	char buffer [1000];
	char com[100];
	int com_counter =0;
	for( int i = 0;  recv_line[i] !=' ' && recv_line[i] != '\n' && recv_line[i] != '\r';i++){
		com[i] = recv_line[i];
		com_counter ++;
	}
	com[com_counter] = 0;
	if(strcmp(com,"name") == 0){ //change name
			// com_counter mean space
		//cout<<"exec name\n";
		char buffer1 [1000];
		int counter1 = 0;
		char new_name[100];
		for(int i=com_counter+1 ;recv_line[i]!='\n' && recv_line[i] !='\r'; i++){
			new_name[counter1] = recv_line[i];
			counter1 ++;
		}
		new_name [counter1] = 0;
		if(strcmp(new_name,"anonymous") == 0){
			sprintf(buffer1,"[Server] ERROR: Username cannot be anonymous.\n");
			write(c_socket[rec],buffer1,strlen(buffer1));
		}
		bool name_avalibale =true ;
		bool name_unique = true ;
		int check_counter = counter1 ;
		
		//cout<<counter1<<" ";
		/*if( (counter1 <2) || (counter1 >12) ){
			name_avalibale =false ;
		}*/
		
		//cout<<name_avalibale<<" ";
		for(int i=5;i<5+check_counter;i++){
			
			if( (counter1 <2) || (counter1 >12) ){
			name_avalibale =false ;
			}
		    else if((recv_line[i] >= 'A' && recv_line[i] <= 'Z') || (recv_line[i] >= 'a' && recv_line[i] <= 'z')) 
			{
			name_avalibale = true;
			}
			else{
			name_avalibale = false;
			break;
			}
		}
		int check_id = rec;
		for(int i=0;i<100;i++){
			if(strcmp (c_name[i],new_name)==0){
				if(i == check_id){
					continue;
				}
				else{
					name_unique = false;
					break;
				}
				
			}
		}
		if(name_avalibale == false){
			sprintf(buffer1,"[Server] ERROR: Username can only consists of 2~12 English letters.\n");
			write(c_socket[rec],buffer1,strlen(buffer1));
		}
		else if(name_unique == false){
			for(int i=0;i<=maxi;i++)
			{
				if(i == rec)
				{
					sprintf(buffer1,"[Server] ERROR: %s has been used by others.\n",new_name);
					write(c_socket[i],buffer1,strlen(buffer1));
				}
				else
				{
					continue;
				}
			
			}
		}
		else{  //success
			sprintf(buffer1,"[Server] You're now known as %s.\n",new_name);
			write(c_socket[rec],buffer1,strlen(buffer1));
			
			//let other know this user change name
			for(int i = 0;i < 100;i++)
			{
				if(i == rec)
				{
					continue;
				}
				else
				{
					sprintf(buffer1,"[Server] %s is now known as %s.\n",c_name[rec],new_name);
					write(c_socket[i],buffer1,strlen(buffer1));
				}
			}
			strcpy(c_name[rec],new_name);
			is_name[rec] = true; 
		}
		
	}
	
	else if(strcmp (com ,"who") == 0){
		//cout<<"exec who\n";
		char bufferh[1000];
		for(int i=0;i<=maxi;i++){
			if( i== rec){
				sprintf(bufferh,"[Server] %s %s/%hu ->me\n",c_name[i],c_ip[i],c_port[i]);
				write(c_socket[rec],bufferh,strlen(bufferh));	
			}
			else  if(c_socket[i] != -1){
				sprintf(bufferh,"[Server] %s %s/%hu\n",c_name[i],c_ip[i],c_port[i]);
				write(c_socket[rec],bufferh,strlen(bufferh));
			}
			
		}
	}
	else if(strcmp(com,"yell")==0){
		//cout<<"exec yell\n";
		char buffer2 [1000];
		char yell_mes[1000];
		int counter4 =0;
		for(int i = com_counter +1 ;recv_line[i] != '\n';i++)
		{
		yell_mes[counter4] = recv_line[i];
		counter4++;
		}
		yell_mes[counter4]=0;
		for(int i = 0;i <= maxi;i++)
		{
		sprintf(buffer2,"[Server] %s yell %s\n",c_name[rec],yell_mes);
		write(c_socket[i],buffer2,strlen(buffer2));
		}	
	}
	else if(strcmp(com,"tell") == 0)
	{
		//cout<<"exec tell\n";
		char sent_name[100];
		char buffer3 [1000];
		bool exist =false ;

		
		int counter = 0;
		int com_counter1;
		int ccc =com_counter +1;
		char sent_mes[1000];
		for(com_counter1 = com_counter +1 ;recv_line[com_counter1] != ' ';com_counter1++)
		{
		sent_name[counter] = recv_line[com_counter1];
		counter++;
		ccc =ccc+1;
		}
		sent_name[counter]=0;
		int mes_counter = 0;
		
		
		
		for(int i =ccc;recv_line[i] != '\n';i++)
		{
		sent_mes[mes_counter] = recv_line[i];
		mes_counter++;
		}
		sent_mes[mes_counter]=0;
		for(int i = 0;i <= maxi;i++)
		{
			if(strcmp(sent_name,c_name[i]) == 0)
			{
				exist = true;
			}
		}
		if(exist ==false){
			sprintf(buffer3,"[Server] ERROR: The receiver doesn't exist.\n");
			write(c_socket[rec],buffer3,strlen(buffer3));
		}
		else if(strcmp(c_name[rec],"anonymous") == 0){
			sprintf(buffer3,"[Server] ERROR: You are anonymous.\n");
			write(c_socket[rec],buffer3,strlen(buffer3));
		}
		else if(strcmp(sent_name,"anonymous") == 0)
		{
			sprintf(buffer3,"[Server] ERROR: The client to which you sent is anonymous.\n");
			write(c_socket[rec],buffer3,strlen(buffer3));
		}
		else{ //sent successful
			for(int i=0;i<=maxi;i++){
				if(i == rec){ // user self
					sprintf(buffer3,"[Server] SUCCESS: Your message has been sent.\n");
					write(c_socket[i],buffer3,strlen(buffer3));
				}
				else{
					sprintf(buffer3,"[Server] %s tell you %s\n",c_name[rec],sent_mes);
					write(c_socket[i],buffer3,strlen(buffer3));
				}
			}
			
			
		}
		
	}
	else{
		//cout<<"exec error\n";
		sprintf(buffer,"[Server] ERROR: Error command.\n");
		write(c_socket[rec],buffer,strlen(buffer));
	}
	
}

int main(int argc , char **argv ){
	int listen_fd ;
	int sockfd;
	struct sockaddr_in servaddr; 
	struct sockaddr_in c_addr;
	int connect_fd;
	int c_socket[100]={0};
	char recv_line[1000];
	for(int i=0;i<100;i++)
	{
		is_name[i] = false;
	}
	
	
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(1031);  //server_port = 1027
	
	if( (listen_fd = socket(AF_INET , SOCK_STREAM , 0 ) ) < 0 )
	{
		cout<<"socket error.\n";
		return  0;
	}
	
	if( (bind(listen_fd,(struct sockaddr *)&servaddr,sizeof(servaddr) ) ) <0  ){
		cout<<"Bind error.\n";
		return 0;
	}
	if ( (listen (listen_fd , 100)) < 0){
		cout<<"listen error.\n";
		return 0;
	}
	fd_set r_set;
	fd_set all_set ;
	FD_SET ( listen_fd , &all_set) ; 
	//FD_ZERO(&c_set);
	int max_fd  = listen_fd +1;
	int c_ready = 0;
	int rec  =0;
	socklen_t ca_len =0;
	int maxi = -1;
	int n=0;
	
	for(int i=0;i<100;i++){
		c_socket[i] = -1; 
	}
	FD_ZERO(&all_set);
	FD_SET ( listen_fd , &all_set) ; 
	
	while (1){
		
		r_set  = all_set;
		c_ready = select( max_fd , &r_set,NULL,NULL,NULL ) ;
		// wait for fist connect
		
		if( FD_ISSET(listen_fd, &r_set ) ){
			
			socklen_t 	clilen =sizeof(c_addr);
			connect_fd = accept (listen_fd , (struct sockaddr *)&c_addr ,&clilen ); //create new socket for new user
			for(rec =0;rec<100;rec++){
				if(c_socket[rec] == -1){
					c_socket[rec] = connect_fd; //record client socket_id
					break ;
				}
			}
			hello( c_socket , rec , &c_addr , maxi);
			
			if(rec == 100){
				cout<<"The server has 100 users. Please wait.\n";
				return 0;
			}
			FD_SET(connect_fd, &all_set);
			if(rec > maxi){
				maxi = rec;
			}
			if( (connect_fd+1) > max_fd){
				max_fd = connect_fd +1 ;
			}
			if(--c_ready <= 0 ){
				continue; //jump to point
			}
			
		}
		
		for(int j=0;j<=maxi;j++){
			if( (sockfd=c_socket[j]) <0 ){
				continue;
			}
			if(FD_ISSET(sockfd,&r_set)){
				if((n = read(sockfd ,recv_line,1000)) == 0){
					for(int i=0;i<=maxi;i++){
						/*if(i == j){
							//continue;
							for(int k=0;k<50;k++)
								c_name [i][k] ='\0';
							
							is_name[j] =false;
							continue;
						}*/
						if(i != j){
							char buffer7[1000];
							sprintf(buffer7,"[Server] %s is offline\n",c_name[j]);
							write(c_socket[i],buffer7,strlen(buffer7));
						}
					}
					close(sockfd);
					FD_CLR(sockfd , &all_set);
					for(int k=0;k<50;k++)
						c_name [j][k] ='\0';
							
					is_name[j] =false;
					c_socket[j] = -1;
					
				}
				else{
					/*char buffer8[1000];
					sprintf(buffer8,"%s\n",recv_line);
					write(c_socket[rec],buffer8,strlen(buffer8));*/
					command(c_socket , maxi ,j ,recv_line);
				}
				if(--c_ready <= 0){
					break ;
				}
				
			}
			
		}	
	}
	return 0;
}

