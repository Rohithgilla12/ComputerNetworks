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
#include <time.h>
#define MAXLINE 1500000 
#define LISTENQ 5

typedef struct sockaddr SA;

int main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE]={'\0'};
	char c;
	char *filesize;
	time_t ticks;
	FILE *filePointer = fopen(argv[1], "rb"); 		
	fseek(filePointer, 0L, SEEK_END);
	long int res = ftell(filePointer);
	printf("%ld",res);
	fclose(filePointer);
	filePointer = fopen(argv[1], "rb"); 		
	// size_t charCount =0;
	// char ch;
	// int i=0;
	// c = fgetc(filePointer);
	// while(c!=EOF){
	// 	buff[i] = c;
	// 	c = fgetc(filePointer); 
	// 	i++;
	// }
	// // printf("%d",i);
	// for(int ij = 0; ij < 10; ij++)
	// {
	// 	i = 0;
	// 	fread(buff, sizeof(buff), 1, filePointer);
	// 	while (i < MAXLINE)
	// 	{
	// 		printf("%c", buff[i]);
	// 		i++;
	// 	}
	// }
	
	// fread(buff, sizeof(buff),1,filePointer);
	// while (i< MAXLINE){ 
    //     printf ("%c", buff[i]); 
	// 	i++; 
    // } 
	/* change this*/
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(5500); /* change this */
	struct sockaddr_in cliaddr;
	socklen_t consize=sizeof(servaddr);
	
	/* change this to regular call*/
	bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

	/* change this*/
	listen(listenfd, LISTENQ);

	printf("Local IP address : %s \n", inet_ntoa(servaddr.sin_addr));

	for (;;)
	{
		// connfd = accept(listenfd, (SA *)NULL, NULL);
		ticks = time(NULL);
//		snprintf(filesize, sizeof(filesize), "%.24s\r\n Gilla", ctime(&ticks));
//		write(connfd, filesize, res);
		// while(!feof(filePointer)){
		// 	fread(buff, sizeof(buff),1,filePointer);
		// 	write(connfd, buff, sizeof(buff));
		// 	bzero(buff, sizeof(buff));	
		// }	
		// while(fread(buff,1, sizeof(buff),filePointer) >0){
		// 	write(connfd, buff, sizeof(buff));	
		// 	bzero(buff, sizeof(buff));	
		// }
	
		fread(buff,1,res,filePointer);
	
		connfd = accept(listenfd, (SA *)NULL, NULL);
		// fread(buff, sizeof(buff),1,filePointer);
		write(connfd, buff, res);
		close(connfd);
	}
}
