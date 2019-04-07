#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXLINE 1500000

void err_sys(const char *x)
{
	perror(x);
	exit(1);
}

void err_quit(const char *x)
{
	perror(x);
	exit(1);
}

typedef struct sockaddr SA;

int main(int argc, char **argv)
{

	int sockfd, n;
	char recvline[MAXLINE + 1]={'\0'};
	struct sockaddr_in servaddr;
	FILE *filePointer = fopen(argv[2], "wb"); 

	if (argc != 3)
		err_quit("usage: a.out <IPaddress>");

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5500); /* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for");

	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	while ((n = read(sockfd, recvline, MAXLINE)) > 0)
	{
		recvline[n] = 0; /* null terminate */
		// if (fputs(recvline, filePointer) == EOF)
		// 	err_sys("fputs error");
		//if(strcpy(recvline,"Gilla")){
			//printf("Found %s",&recvline);
		//}
		//else{
		//for(int i = 0; i < MAXLINE; i++){
			//printf("%c", recvline[i]);
		//}
		fwrite(recvline,1, 26868, filePointer);
		//}
		
				
	}
	if (n < 0)
		err_sys("read error");

	exit(0);
}
