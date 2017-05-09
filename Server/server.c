// Created by Figueroa, Patricia on 5/03/17.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

#define BUF_SIZE 1024

void *ServerEcho(void *args)
{
	 int clientFileDiscriptor=*((int *)args);
	 char buff[BUF_SIZE];
	 strcpy(buff,"Choose :\n1.Login\n");
	 write(clientFileDiscriptor,buff,BUF_SIZE);		// read
	 read(clientFileDiscriptor,buff,BUF_SIZE);
	 int option = atoi(buff);
	 if(option==1)
	 {
	 	printf("1\n");
	 	ServerLogIn(args);
	 }
	
	 close(clientFileDiscriptor);
}

int main(int argc, char **argv)
{
  int port = atoi(argv[1]);
	int i,welcomeSocket, newSocket;
	char buffer[1024];
 	struct sockaddr_in serverAddr;
  	struct sockaddr_storage serverStorage;
  	socklen_t addr_size;
  	pthread_t tid;

  	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  	serverAddr.sin_family = AF_INET;
  	serverAddr.sin_port = htons(port);
  	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
	
  	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  	if(listen(welcomeSocket,5)==0)
    		printf("Listening at port: %d\n",port);
  	else
    		printf("Error\n");

  	addr_size = sizeof serverStorage;
  	for(i=0;i<20;i++)
  	{
  		newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  		printf("New Connection!\n");
  		pthread_create(&tid,NULL,ServerEcho,&newSocket);
  	}
  	close(welcomeSocket);
  	return 0;
}
