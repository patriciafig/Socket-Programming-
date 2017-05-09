// Created by Figueroa, Patricia on 5/01/17.

#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1024

void ClientLogin(void *args)
{
	int clientFileDiscriptor=*((int *)args);
	char buff[BUF_SIZE],*check=NULL;
	strcpy(buff,"Enter Username : \n");
	fputs(buff,stdout);
	fgets(buff,BUF_SIZE,stdin);
	write(clientFileDiscriptor,buff,BUF_SIZE);
	
	read(clientFileDiscriptor,buff,BUF_SIZE);
	fputs(buff,stdout);
	while(strcmp(buff,"Rejected")==0)
	{
		strcpy(buff,"Enter a valid Username : \n");
		fputs(buff,stdout);
		fgets(buff,BUF_SIZE,stdin);
		write(clientFileDiscriptor,buff,BUF_SIZE);
		read(clientFileDiscriptor,buff,BUF_SIZE);
		fputs(buff,stdout);

	}
	if(strcmp(buff,"Accepted")==0)
	{
		strcpy(buff,"Enter Password : \n");
		fputs(buff,stdout);
		fgets(buff,BUF_SIZE,stdin);
		write(clientFileDiscriptor,buff,BUF_SIZE);
		read(clientFileDiscriptor,buff,BUF_SIZE);
		fputs(buff,stdout);
		while(strcmp(buff,"Rejected")==0)
	{
		strcpy(buff,"Enter a valid password : \n");
		fputs(buff,stdout);
		fgets(buff,BUF_SIZE,stdin);
		write(clientFileDiscriptor,buff,BUF_SIZE);
		read(clientFileDiscriptor,buff,BUF_SIZE);
		fputs(buff,stdout);

	}
	}

	
	read(clientFileDiscriptor,buff,BUF_SIZE);
	printf("\n** Execution Complete **\n");
	
	
}
