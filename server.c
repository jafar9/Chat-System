#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<strings.h>
#include<errno.h>
#include<signal.h>
#include<sys/time.h>

struct usersock
{
  char username[7];
  int soc;
}user[100];

void check(int);
void* server(void*);
int nu=0;
int new_sock[100];
int sock_count=0;
int sockfd;

int main(int argc, char *argv[])
{
 
 struct sockaddr_in ser,client; 
 int sock,len,b;
 int port=atoi(argv[1]);
 sock=socket(AF_INET ,SOCK_STREAM ,0);
 ser.sin_family=AF_INET;
 ser.sin_addr.s_addr=INADDR_ANY;
 ser.sin_port=htons(port);
 len=sizeof(ser);
 b=bind(sock,(struct sockaddr *)&ser,sizeof(ser));
 bzero(new_sock,sizeof(new_sock));
 listen(sock,100);
 for(int i=0;i<100;i++) 
 {
  user[i].soc=0;
 }

 while(1)
 {
  new_sock[sock_count]=accept(sock,(struct sockaddr *)&client,&len);
  if(new_sock[sock_count]<0)
   {
    printf("New connections cannot be created\n");
    exit(0);
   }
  pthread_t thread;
  pthread_create(&thread,NULL,server,(void *)&new_sock[sock_count]);
  sock_count++;
 }
 close(new_sock[sock_count]);
 close(sock);
 return 0;
}

void* server(void* sockfd)
{
 int newsockfd=*((int *)sockfd);
 int count;
 check(newsockfd);
 char to[7],from[7],message[1024],step[1024];
 bzero(step,1024);
 for(int i=0;i<nu;i++)
 {
   if(user[i].soc!=0)
   {
    strcat(step,user[i].username);
    strcat(step,"\n");
   }
 }
 printf("tep is %s \n",step);
 int l= send(newsockfd,step,sizeof(step),0);
 printf("no of bytes sent %d \n",l);
while(1)
 {
  int q=recv(newsockfd,&to,sizeof(to),0);
  if(q==0)
  {
   for(int i=0;i<nu;i++)
   {
    if(user[i].soc==newsockfd)
    {
     user[i].soc=0;
  	 strcpy(user[i].username,"\0");
    }
   }
  }
 int x=recv(newsockfd,&from,sizeof(from),0);
  if(x==0)
  {
  for(int i=0;i<nu;i++)
  {
   if(user[i].soc==newsockfd)
   {
    user[i].soc=0;
    strcpy(user[i].username,"\0");
   }
  }
 }
  int y=recv(newsockfd,&message,sizeof(message),0);
    if(y==0)
   {
    for(int i=0;i<nu;i++)
    {
      if(user[i].soc==newsockfd)
      {
       user[i].soc=0;
strcpy(user[i].username,"\0");
      }
    }
   }
   int n,l;
  
int sendsockfd;
for(n=0;n<nu;n++)
   {
    if( (strcmp(user[n].username,to) )==0)
        {
          sendsockfd=user[n].soc;
        }
    }
send(sendsockfd,&from,sizeof(from),0);
send(sendsockfd,&message,sizeof(message),0);
}

}

   
 void check(int new_socket)
{
  char buff[1024],buff1[1024],temp[1024],is[1024],bs[1024],fr[1024];
    int l,count=0;
    recv(new_socket,&l,sizeof(int),0);
    if(l==1)
		{ 
    bzero(buff,1024);
   	bzero(buff1,1024);
		recv(new_socket,&buff,1024,0);
    recv(new_socket,&buff1,1024,0);
    strcpy(temp,buff);
    strcat(buff,buff1);
		FILE *fp;
		fp=fopen("abc1.txt","a+");
    while(!feof(fp))
    { 
		fscanf(fp,"%s",is);
		if(strcmp(is,buff)==0)
		 { 
		  int len1=1024;
      send(new_socket,&len1,sizeof(int),0);
		   count=1;
      check(new_socket);
   	 return; 
     }  
   }
  if(count  != 1)
	{
   int len1=-111;
   send(new_socket,&len1,sizeof(int),0);
		count=0;
	 fprintf(fp,"%s\n",buff);
	 fclose(fp);
  }
}
 bzero(buff,1024);
	int temp1;
	int x=recv(new_socket,&buff,1024,0);
	bzero(buff1,1024); 
	x= recv(new_socket,&buff1,1024,0);
	strcpy(fr,buff);
	strcat(buff,buff1);
	FILE *sp;
	char us[1024],ch[1024];
	sp=fopen("abc1.txt","r");
	int sum=0;
	while(!feof(sp))
	{
	fscanf(sp,"%s",us);
	temp1=strcmp(us,buff);
	if(!temp1){
	int len1=1024;
	strcpy(user[nu].username,fr);
	printf("user name in structure is :%s\n",user[nu].username);
	printf("file desc is :%d\n",new_socket);
  user[nu].soc=new_socket;
  nu++;
  send(new_socket,&len1,sizeof(int),0);
  sum=1;
	break;
	}
}
 fclose(sp);
 if(sum != 1)
 {
	int len1=-111;
  send(new_socket,&len1,sizeof(int),0);
  check(new_socket);
  return;		
 }
 sum=0;
}


