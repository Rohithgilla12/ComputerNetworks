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


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
struct arg{
	int connfd;
	int client_num;
};

void *sock_thread(void *arg){
	pthread_mutex_lock(&lock);
	struct arg given_arg=*(struct arg *)arg;
	int conn_fd=given_arg.connfd;
	int latestClient=given_arg.client_num;	
	char readbuff[1024];

	char fileName[100];
    char clientFileName[1000];
    char numberString[100];	
	int fino= rand() % 1000000 + 1;

    printf("Thread created");
    sprintf(numberString, "%d", latestClient);
    sprintf(clientFileName, "%s", "Client");
    strcat(clientFileName, numberString);
	printf("cl_no=%s \n", clientFileName);
	sprintf(clientFileName,"clientFile_%d",fino);		

    int created_new_file = creat(clientFileName, S_IRWXU);
	
	int bval;
	while ((bval = read(conn_fd, readbuff, 1024)) > 0)
	{
		write(created_new_file, readbuff, bval);
		//printf("%s",readbuff);
	}
	close(created_new_file);
	pthread_mutex_unlock(&lock);
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
	
	pthread_t thid[200];
	char readbuff[1024];
	struct arg example;
	
	char readbuff1[1024];
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(6789);	

	int bval;
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	int new_file=0;

	listen(listenfd, 5);
	
    int cl_no=0;

	char copy[1024];
	int i=0;
	for ( ; ; ) {
        
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &consize);
		i=i+1;
		cl_no = cl_no+1;
		example.connfd=connfd;
		example.client_num=cl_no;
		if (pthread_create(&thid[i],NULL,sock_thread,&example) !=0)
		{
			printf("thread creation problem");
		}
		 
	}
	close(connfd);
	close(listenfd);

	printf("Done with file receive");
	exit(0);
}

