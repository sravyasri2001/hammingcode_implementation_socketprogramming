#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include <unistd.h>
#include<stdlib.h>
#include<math.h>
#define MAX 80
#define SERV_TCP_PORT 8080
#define SA struct sockaddr
int main()
{
int sockfd,newsockfd,clength;
struct sockaddr_in serv_addr,cli_addr;
char a[100],s[100],l[100];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if (sockfd == -1) {
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");

serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=INADDR_ANY;
serv_addr.sin_port=htons(SERV_TCP_PORT);
if ((bind(sockfd, (SA*)&serv_addr, sizeof(serv_addr))) != 0) {
printf("socket bind failed...\n");
exit(0);
}
else
printf("Socket successfully binded..\n");
if ((listen(sockfd, 5)) != 0) {
printf("Listen failed...\n");
exit(0);
}
else
printf("Server listening..\n");
clength=sizeof(cli_addr);
newsockfd=accept(sockfd, (SA*)&cli_addr, &clength);
if (newsockfd< 0) {
printf("server acccept failed...\n");
exit(0);
}
else
printf("server acccept the client...\n");
read(newsockfd,s,sizeof(s));
int k=strlen(s);
l[0]=s[k-1];
k=k-1;
s[k]='\0';
s[3]='0';
l[1]='\0';
int h=0,count1=0,p=0,count=0;
for(int i=0;i<k;i++)
{
	if(i==pow(2,h)-1)
	{
	count++;
	h++;
	}
}
h=0;
for(int i=0;i<count;i++)
{
int count1=0;
	for(int j=1;j<=k;j++)
	{		
		if(1&(j>>h))
		{
			if(s[k-j]=='1')	
				count1++;
		}
	}
	if(l[0]=='0')
	{
		if(count1 %2==0)
			a[count-1-p]='0';
		else
			a[count-1-p]='1';
		p++;
	}
	else
	{
		if(count1 %2==0)
			a[count-1-p]='1';
		else
			a[count-1-p]='0';
		p++;
	}
	h++;
}
a[h]='\0';
write(newsockfd,a,sizeof(a));
close(sockfd);
}
