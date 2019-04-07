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

int main(int argc, char **argv)
{
	int listenfd, connfd;
	pid_t pid;
	struct sockaddr_in servaddr;
	char buff[1024];
	int counter =0;
	struct sockaddr_in cliaddr;
	socklen_t consize = sizeof(servaddr);
	int fildes;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(6789); /* change this */

	char readbuff[1024];
	int createdfile = creat("newfile", S_IRWXU);

	/*fildes=open(argv[1], O_RDONLY);*/

	int bval;

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, 5);

	for (;;)
	{
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &consize);
		if ((pid = fork()) == -1)
		{
			close(connfd);
			continue;
		}
		else if(pid > 0){
			close(connfd);
			counter++;
			printf("%d",counter);
			printf("here2\n");
			continue;
		}
		else if(pid ==0 ){
			printf("connection received\n");
			while ((bval = read(connfd, readbuff, 1024)) > 0)
				write(createdfile, readbuff, bval);
				close(connfd);
				printf("%d",counter);
				// break;			
		}
		/*change this */
		        	
		

		// close(connfd);
		// close(listenfd);
		// close(createdfile);
		// printf("Done with file receive");
		// exit(0);
	}
}
