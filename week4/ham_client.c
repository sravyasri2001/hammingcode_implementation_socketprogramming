#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
#include<math.h>
#define MAX 80
#define SERV_TCP_PORT 8080
#define SA struct sockaddr
int main()
{
int sockfd,connfd;
struct sockaddr_in serv_addr;
char d[100];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if (sockfd == -1) 
{
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");

bzero(&serv_addr, sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
serv_addr.sin_port=htons(SERV_TCP_PORT);

if (connect(sockfd, (SA*)&serv_addr, sizeof(serv_addr)) != 0)
{
printf("connection with the server failed...\n");
exit(0);
}
else
printf("connected to the server..\n");


printf("Enter data to be transmitted:\n");
scanf("%s",d);
char parity;
printf("Press 0 for even parity else press 1 for odd parity:\n");
scanf("\n%c",&parity);

int p=0,m;
m=strlen(d);
while(pow(2,p)<m+p+1)
	p++;

int k=p+m,g=0,h=0;
char s[100];
for(int i=0;i<k;i++)
{
	if(i==pow(2,h)-1)
	{
		s[k-i-1]='-';
		h++;
	}
	else
	{
		s[k-1-i]=d[m-1-g];
		g++;
	}
}

h=0;
for(int i=0;i<k;i++)
{
	if(i==pow(2,h)-1)
	{
		int count=0;
		for(int j=1;j<=k;j++)
		{
			
			if(1&(j>>h))
			{
				if(s[k-j]=='1')
				{			
				count++;
				}
			}
		}
		if(parity=='0')
		{
			if(count%2==0)
				s[k-1-i]='0';
			else
				s[k-1-i]='1';
		}
		else
		{
			if(count%2==0)
				s[k-1-i]='1';
			else
				s[k-1-i]='0';
		}
		h++;
	}
	
}
char t[100];
s[k]=parity;
s[k+1]='\0';
//printf("%s",s);
write(sockfd,s,sizeof(s));
printf("\nMessage from Server:\n");
read(sockfd,t,sizeof(t));
int a=0,v=0;
for(int i=strlen(t)-1;i>=0;i--)
{
	a=a+(t[i]-'0')*(pow(2,v));
	v++;
}
if(a==0)
printf("Data succesfully received...\n");
else
{
printf("Data got corrupted during transmission...\n");
printf("Error occurred at position: %d\n",a+1);
}
close(sockfd);
return 0;
}

