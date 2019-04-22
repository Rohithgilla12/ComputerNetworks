#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>

struct arg{
	int confd;
	int fileno;
};

void *threadSendFunction(void *argument){
	struct arg fdd=*(struct arg *)argument;
	int cfdd=fdd.confd;
	int none=fdd.fileno;
	int fino= rand() % 100000 + 1;;
	char readbuff[1024];
	fino += 1;
	char fileName[100];
	sprintf(fileName, "Client%d", fino);
	int bval;
	int createdfile=creat(fileName, S_IRWXU);
	while ((bval = read(cfdd, readbuff, 1024)) > 0)
	{
		write(createdfile, readbuff, bval);
		printf("%s",readbuff);
	}
	close(createdfile);
	return NULL;
}

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[1024];
	struct sockaddr_in cliaddr;	
	socklen_t consize=sizeof(servaddr);	
	int fildes; 
	pthread_t thid[10];
	char readbuff[1024];
	struct arg inst;
	

	char readbuff1[1024];
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(6789);	/* change this */
	int bval;
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	int createdfile=0;
	listen(listenfd, 5);
	char a[10]="client_";
    int y=0;
	char *token;
	char copy[1024];
	int i=0;
	for ( ; ; ) {
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &consize);		
		i=i+1;
		y = y+1;
		inst.confd=connfd;
		inst.fileno=y;
		pthread_create(&thid[i],NULL,threadSendFunction,&inst);			
	}
	close(connfd);
	close(listenfd);

	printf("Done with file receive");
	exit(0);
}

