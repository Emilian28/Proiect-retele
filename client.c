#include "lib/sinc.h"


int 
main(int argc, char **argv)
{
	argc_length(argc, 2);
	
	int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	memset(&server4_address, 0, sizeof(server4_address));
	server4_address.sin_family = AF_INET;
	server4_address.sin_port = htons(PORT);
	Inet_pton(AF_INET, argv[1], &server4_address.sin_addr);
	
	Connect(listenfd, (SA* )&server4_address, sizeof(server4_address));
	
	str_cli(stdin, listenfd);

	exit(EXIT_SUCCESS);
}

