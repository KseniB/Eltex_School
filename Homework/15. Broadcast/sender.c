#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>          
#include <sys/stat.h>


#define B_PORT 7777
#define B_ADDRES "224.0.0.1"

int main(){

	char buffer[80] = "Broadcast msg";
	int fd;
	int len;

	struct sockaddr_in server;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &(int){1}, sizeof(int)) == -1)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	memset(&server, 0, sizeof(server));
	
	server.sin_family = AF_INET;  
	server.sin_addr.s_addr = inet_addr(B_ADDRES);
	server.sin_port = htons(B_PORT); 
	
	len = sizeof(server);

	if (sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr*)&server, len) == -1)
	{
		perror("sendto");
		exit(EXIT_FAILURE);
	}

	return 0;
}
