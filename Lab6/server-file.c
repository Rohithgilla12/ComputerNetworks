#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[1024];
	struct sockaddr_in cliaddr;
	socklen_t consize = sizeof(servaddr);
	int fildes;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(6789); /* change this */

	char readbuff[1024];

	int bval;

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, 5);
	char filename[12];

	int fileIndex = 1;
	for (;;)
	{

		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &consize);
		if (connfd < 0)
		{
			exit(1);
		}
		fileIndex += 1;
		printf("Connection Received\n");
		pid_t childpid;
		if ((childpid = fork()) == 0)
		{
			sprintf(filename, "Client%d", fileIndex);
			int createdfile = creat(filename, S_IRWXU);
			close(listenfd);

			while ((bval = read(connfd, readbuff, 1024)) > 0)
			{
				write(createdfile, readbuff, bval);
			}
			close(createdfile);
			close(connfd);					
		}
		else if (childpid == -1)
		{
			// close(connfd);
			continue;
		}
	}
}
