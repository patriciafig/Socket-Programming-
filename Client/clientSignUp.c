// Created by Figueroa, Patricia on 5/01/17.
#include<stdio.h>
#include<string.h>

#define BUF_SIZE 1024

void ClientSignup(void *args)
{
	printf("here\n");
	int clientFileDiscriptor=*((int *)args);
	char buff[BUF_SIZE];
	
	read(clientFileDiscriptor,buff,BUF_SIZE);
	fputs(buff,stdout);
	fgets(buff,BUF_SIZE,stdin);
  	write(clientFileDiscriptor,buff,BUF_SIZE);	// set username
  	
  	read(clientFileDiscriptor,buff,BUF_SIZE);
	fputs(buff,stdout);
	
}
