#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<errno.h>
#include<sys/wait.h>
int sockid;
void check();
int main(int argc,char *argv[])
{
	char to[100],from[100],buffer[1024],online[1024];
	struct sockaddr_in server;
	if((sockid=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket:");
		exit(0);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;	
	bzero(&server.sin_zero,8);
	int len=sizeof(struct sockaddr_in);
	if((connect(sockid,(struct sockaddr *)&server,len))==-1)
	{
 		perror("connect:");
		exit(0);
	}
	int rel,te;
	check();
	puts("online users");
	int l=recv(sockid,&online,sizeof(online),0);
	printf("%s",online);
	pid_t  pid=fork();
	if(pid==0)
	{
		while(1)
		{ 
		  bzero(to,1024);
		  printf("Enter the receiver's username\n");
			scanf("%s",to);
			send(sockid,&to,sizeof(to),0);
			bzero(to,1024);
			printf("Enter your username\n");
			scanf("%s",to);
			send(sockid,&to,sizeof(to),0);
			bzero(to,1024);
			printf("Enter the message\n");
			fgets(to,1024,stdin);
			send(sockid,&to,sizeof(to),0);
		}
	}
	else	
	{
		while(1)
		{
			int n=recv(sockid,&from,sizeof(from),0);
			n=recv(sockid,&buffer,sizeof(buffer),0);
			printf("you got a message from %s\n",from);
			printf("message:%s\n",buffer);
			bzero(buffer,1024);
		}
	}
	close(sockid);
	return(0);
}

void check()
{
int len;
  char ch1,buff[1024];
  printf("select option 1.signup or 2.signin\n");
  scanf("%d",&len);
  
send(sockid,&len,sizeof(int),0);
  
 if(len == 1)
  { 
  puts("enter user name"); 
  scanf("%s",buff);
  send(sockid,&buff,strlen(buff),0);
  puts("enter password");
  bzero(buff,1024);
  scanf("%s",buff);
  send(sockid,&buff,strlen(buff),0);
  recv(sockid,&len,sizeof(int),0);
  if(len == 1024)
  {
   printf("user deatils already exist\n");
   check();
   return;
  }
  else
  {
    printf("registred success\n");
  }
} 
  bzero(buff,1024);
  printf("enter login details\n");
  scanf("%s",buff);  
  int x=send(sockid,&buff,strlen(buff),0);
  puts("enter password");
  bzero(buff,1024);
  scanf("%s",buff);
  x=send(sockid,&buff,strlen(buff),0);
  recv(sockid,&len,sizeof(int),0);
  if(len==1024)
  {
   printf("login successfull\n");
   return;
  }
  else
   {
  puts("invalid login details");
   check();
   return;
  }



  
   

}
