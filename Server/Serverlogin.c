// Created by Figueroa, Patricia on 5/03/17.

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#define BUF_SIZE 1024

int validate(char *name)//Validating username
{
	//printf("length of username is:%d",strlen(name));
	if(strlen(name)>12)//length of user nae should not exceed 12 characters
		return 0;
	int iter=0;
	for(iter=0;iter<strlen(name);iter++)//user name should only have alphanumerics 
	{
		if(name[iter]<48 || name[iter]>122)
			return 0;
		if(name[iter]>57 && name[iter]<65)
			return 0;
		if(name[iter]>90 && name[iter]<97)
			return 0;

	}

	return 1;
}
int validate_password(char *name)//Validating password
{
	//printf("length of username is:%d",strlen(name));
	int iter=0;
	if(strlen(name)>30)//length of password field should not exceed 30 characters
		return 0;
	for(iter=0;iter<strlen(name);iter++)//verifying restrictions on password
	{
		if(name[iter]<48 && name[iter]!='!' && name[iter]!='$'  && name[iter]!='&' && name[iter]!='*' && name[iter]!=')' && name[iter]!='(' && name[iter]!='+'  )
			return 0;
		if(name[iter]>57 && name[iter]<65 && name[iter]!='?' && name[iter]!='@')
			return 0;
		if(name[iter]>90 && name[iter]<97 && name[iter]!='^')
			return 0;
		if(name[iter]>122 && name[iter]!='~')
			return 0;

	}

	return 1;
}
/*void TimeCounter(time_t *time_start)
{

	//make the time process sleep for 30 seconds
	
	while((time(NULL)-*time_start)<30)
		;
	printf("30 seconds expired, please try again.\n");
	//pthread_exit(NULL);

}
*/
void ServerLogIn(void *args)
{
	const char s[2] = " ";
	int clientFileDiscriptor=*((int *)args);
	char buff[BUF_SIZE],buf[BUF_SIZE],*uname,*password,*name_pwd,user_name[100],pwd[100],*temp,*untoken,*pwdtoken,matched='n',name[100];
	pthread_t tid;
	time_t time_start=time(NULL);
	//pthread_create(&tid,NULL,TimeCounter,&time_start);
	read(clientFileDiscriptor,buff,BUF_SIZE);	// read username
	if(time(NULL)-time_start>30)//updating time
	{
		//printf("Entering the time allotment routine :%u \n",(time(NULL)-time_start) );
		temp=strtok(buff,"\n");
		strcpy(buff,"Time limit exceed.");
		write(clientFileDiscriptor,buff,BUF_SIZE);
		printf("Time limit exceed. Closing connection");
		//pthread_exit(NULL);
		return;


	}
	printf("%s",buff );
	uname=strtok(buff,"\n");
	//printf("length of username (%s) is:%d",uname,strlen(uname));
	int valid = validate(uname);
	while(valid==0)
	{
		printf("Invalid Username entered\n");
		strcpy(buff,"Rejected");
		write(clientFileDiscriptor,buff,BUF_SIZE);
		time_start=time(NULL);
		read(clientFileDiscriptor,buff,BUF_SIZE);
		if(time(NULL)-time_start>30)//updating time
		{
		strcpy(buff,"Time limit exceed.");
		write(clientFileDiscriptor,buff,BUF_SIZE);
		printf("Time limit exceed. Closing connection");
		return;
		//pthread_exit(NULL);

		}
		uname=strtok(buff,"\n");
		valid=validate(uname);

	}
	
	
		strcpy(name,uname);
		strcpy(buff,"Accepted");
		write(clientFileDiscriptor,buff,BUF_SIZE);
		read(clientFileDiscriptor,buff,BUF_SIZE);	// read password
		time_start=time(NULL);
		if(time(NULL)-time_start>30)//updating time
		{
			strcpy(buff,"Time limit exceed.");
			write(clientFileDiscriptor,buff,BUF_SIZE);
			printf("Time limit exceed. Closing connection");
			//pthread_exit(NULL);
			return;
		}
		printf("%s", buff);
		password=strtok(buff,"\n");
		valid=validate_password(password);
		while(valid==0)
		{
			printf("Invalid password\n");
			strcpy(buff,"Rejected");
			write(clientFileDiscriptor,buff,BUF_SIZE);
			time_start=time(NULL);
			read(clientFileDiscriptor,buff,BUF_SIZE);
			if(time(NULL)-time_start>30)//updating time
			{
				strcpy(buff,"Time limit exceed.");
				write(clientFileDiscriptor,buff,BUF_SIZE);
				printf("Time limit exceed. Closing connection");
				//pthread_exit(NULL);
				return;
			}
			password=strtok(buff,"\n");
			valid=validate_password(password);


		}
		strcpy(pwd,password);
		name_pwd=malloc(strlen(name)+1+strlen(pwd));
		strcat(name_pwd,name);
		strcat(name_pwd,"\t");
		strcat(name_pwd,pwd);
		printf("The username password pair is %s\n",name_pwd );
	
	
	
	FILE *fptr;
	fptr=fopen("UserInfo.txt","r");
	printf("Name: %s and password: %s\n",name,pwd);
	while (fgets(buf,1000, fptr)!=NULL)
        	{	
        		untoken = strtok(buf, s);
        		//strcpy(user_name,untoken);
        		pwdtoken = strtok(NULL, "\n");
			printf("Comparing %s %s with %s %s from file",name,pwd,untoken,pwdtoken);
        		if(/*searchActiveUsers(name)==0 &&*/ strcmp(name,untoken)==0 && strcmp(pwd,pwdtoken)==0)
        		{
				
        			strcpy(buff,"LogIn Successfull. User found\n");	// Session starts here
        			write(clientFileDiscriptor,buff,BUF_SIZE);
        			matched = 'y';
        			
        			break;
        		}
		}
	if(matched=='n')
		{
			strcpy(buff,"Login Failed.Try Again!!");
        		write(clientFileDiscriptor,buff,BUF_SIZE);		
		}		
		fclose(fptr);
}
