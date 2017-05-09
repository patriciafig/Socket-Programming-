// Created by Figueroa, Patricia on 4/29/17.

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#define BUF_SIZE 1024
int main(int argc, char **argv){
  printf("Connecting to server: %s\t",argv[1] );
  int port = atoi(argv[2]);
  printf("at port: %d\n",port );
  int clientSocket;
  char buffer[BUF_SIZE];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);//Setting the servers port number
 
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);//Setting the servers ip addr
 
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

 
  addr_size = sizeof serverAddr;
  int connect_status = connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  if(connect_status==0)
    printf("Connection established.\n");
  else
    printf("Connection refused.\n");

 
  read(clientSocket, buffer, BUF_SIZE);	
  fputs(buffer,stdout);
  
  strcpy(buffer,""); 
  fgets(buffer,BUF_SIZE,stdin);
  write(clientSocket,buffer,BUF_SIZE);
  
  int option = atoi(buffer);
  option=1;
  if(option == 1)
  {
  	ClientLogin(&clientSocket);
  }
  
   
  return 0;
}
