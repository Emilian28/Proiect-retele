#include "sinc.h"


int
Socket(int domain, int type, int protocol)
{
	int sockfd = socket(domain,type,protocol);
	if(sockfd == -1)
		prog_error("Socket error",true,errno);
	return sockfd;
}

void
Connect(int socket, const struct sockaddr *address, socklen_t address_len)
{
	int connection = connect(socket, address, address_len);
	if(connection < 0)
		prog_error("Connect error",true,errno);
}

void
Bind(int socket,const struct sockaddr *address,socklen_t address_len)
{
	int rbind = bind(socket,address ,address_len);
	if(rbind == -1)
		prog_error("Bind error",true,errno);
}
void
Listen(int socket, int backlog)
{
	int rlisten = listen(socket,backlog);
	if(rlisten == -1)
		prog_error("Listen error",true,errno);
}
int
Accept(int socket, struct sockaddr  *restrict address, socklen_t  *restrict address_len)
{
	int raccept;
	raccept = accept(socket,address,address_len);
	if(raccept == -1)
		prog_error("Accept error",true,errno);

	return raccept;
}

/*Wrapper write*/
ssize_t
Write(int fd, const void *buffer,size_t len_buffer)
{
	ssize_t nbytes_writen = write(fd,buffer,len_buffer);

	if(nbytes_writen == -1)
		prog_error("Write error",true,errno);

	return (ssize_t)len_buffer;
}

ssize_t
Read(int fd, void *buffer, size_t len_buffer)
{
	ssize_t nbytes_readed = read(fd,buffer,len_buffer);

	if(nbytes_readed == -1)
		prog_error("Read error",true,errno);

	return (ssize_t)len_buffer;
}

/*
 * Presentation to network byte order
 */
void 
Inet_pton(int af, const char *src, void *dst)
{
	int inet = inet_pton(af,src,dst);

	if(inet == -1)
		prog_error("Ip conversion error",true,errno);
	else
		if(inet == 0)
			prog_error("Invalid ip address",false,errno);
}
void
Close(int fd)
{
	if(close(fd) == -1)
		prog_error("Clode error",true,errno);
}
pid_t
Fork(void)
{
	pid_t pid;
	if((pid = fork()) < 0)
		prog_error("Fork error",true,errno);
	return pid;
}

pid_t
Waitpid(pid_t pid,int *ptr,int mode)
{
    pid_t rpid;
    rpid = waitpid(pid,ptr,mode);

    if(rpid == -1)
        prog_error("Waidpid error",true,errno);
    return rpid;
}

pid_t
Wait(int *status)
{
    pid_t rpid;

    rpid = wait(status);
    if(rpid == -1)
        prog_error("Wait error",true,errno);
    return rpid;
}
/*
 * Our own standard I/O wrapper functions
 */
char *
Fgets(char *pointer,int n, FILE *stream)
{
	char *fpointer = fgets(pointer,n,stream);
	int file_error = ferror(stream);

	// if fgets returned null and ferror return true
	if( (fpointer == NULL) && (file_error) ) {
        echo_error("Can't read line from stdin",true,errno);
		return NULL;
	}
	return fpointer;
}
void
Fputs(const char *pointer, FILE *stream)
{
	if(fputs(pointer,stream) == EOF )
	 	prog_error("Can't output line from buffer given",true,errno);
}
