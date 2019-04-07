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
#include<malloc.h>

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[1024];
	struct sockaddr_in cliaddr;	
	socklen_t consize=sizeof(servaddr);	
	int fildes; 


	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(6789);	/* change this */


        char readbuff[1024];
        int createdfile=creat("newfile", S_IRWXU);


        /*fildes=open(argv[1], O_RDONLY);*/

	int bval;


	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	

	listen(listenfd, 5);


	for ( ; ; ) {
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &consize);

	/*change this */
printf("connection received\n");

while((bval=read(connfd, readbuff, 1024))>0) 
        	write(createdfile, readbuff, bval);

		close(connfd);
		close(listenfd);
		close(createdfile);
		perror("Done with file receive");
		exit(0);

	}
}
