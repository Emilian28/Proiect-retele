#include "sinc.h"

void 
str_echo(int sockfd) {
	ssize_t n;
	char buffer[MAXLINE];
		while((n = read(sockfd, buffer, MAXLINE)) > 0){
			s_write(sockfd,buffer,MAXLINE,true);
		}
}

void 
str_cli(FILE *stream, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];
	while(Fgets(sendline,MAXLINE, stream) != NULL) {
		s_write(sockfd, sendline, strlen(sendline), true);
		if(readline(sockfd, recvline, MAXLINE) == 0) {
			prog_error("server exit prematurely\n",true, errno);
		}
		Fputs(recvline, stdout);
	}
}


