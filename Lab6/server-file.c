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
//#include<malloc.h>

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[1024];
	struct sockaddr_in cliaddr;	
	socklen_t consize=sizeof(servaddr);	
	int fildes; 

    pid_t child_pid;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(6789);	/* change this */

        char readbuff[1024];
        //int createdfile=creat("newfile", S_IRWXU);
        /*fildes=open(argv[1], O_RDONLY);*/

	int bval;
	pid_t cpid;
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	listen(listenfd, 5);
    int client_count=0;
	char num_str[100];
	char client_var[1000];
	for ( ; ; ) 
    {	
		printf("\n here waiting for a client\n");
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &consize);
        client_count=client_count+1;
        /*change this */
        printf("connection received\n");
        int file_no=0;
		char file_var[100];
        if ((child_pid=fork())==0)
        {	

			file_no=file_no+1;
            printf ("%s\n","a Child created for dealing with client requests");
            sprintf(num_str,"%d",client_count);
			//close(listenfd);
			sprintf(client_var,"%s","client");
			strcat(client_var,num_str);
			strcat(client_var,"_");
			sprintf(file_var,"%d",file_no);
			strcat(client_var,file_var);
			printf("cl_no=%s \n",client_var);
            int created_new_file=creat(client_var, S_IRWXU);
            //close listening socket
            //close (listenfd);
			//printf("client no:%s",num_str);
            while((bval=read(connfd, readbuff, 1024))>0) 
			{
        	    write(created_new_file, readbuff, bval);
				//puts(readbuff);
			}

            printf("Transfer Done\n");
			close(created_new_file);
            exit(0);
        }
		else
		{
			printf("\nwaiting for a client\n");
			cpid=wait(NULL);
		}
		close(connfd);

	}
}
