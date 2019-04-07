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
	int sockfd, n;
	char recvline[1024];
	struct sockaddr_in servaddr;
	socklen_t consize = sizeof(servaddr);
	/*int createdfile=creat("newfile", S_IRWXU);*/

	int fildes = open(argv[2], O_RDONLY);

	char readbuff[1024];

	if (argc != 3)
	{
		printf("usage: a.out <IPaddress> <filename>");
		exit(0);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error");
		exit(0);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6789); /* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		printf("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (struct sockaddr *)&servaddr, consize) < 0)
		printf("connect error");


	while ((n = read(fildes, recvline, 1024)) > 0)
	{
		write(sockfd, recvline, n);
		/*lseek(fildes, bval, SEEK_SET);*/
	}
	close(fildes);
	if (n < 0)
		exit(printf("read error"));

	exit(0);
}
