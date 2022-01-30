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

int main()
{
	int fd;
	char buffer[80];
	int len;
    
	struct sockaddr_in server, client;
    
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
    	perror("socket");
    	exit(EXIT_FAILURE);
	} 
	
	memset(&server, 0, sizeof(server));
	
	server.sin_family = AF_INET;  
	server.sin_addr.s_addr = inet_addr(B_ADDRES);
	server.sin_port = htons(B_PORT);
	
	len = sizeof(server);

	if (bind(fd, (struct sockaddr*)&server, sizeof(server)) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len) == -1)
	{
		perror("recvfrom");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", buffer);
}
