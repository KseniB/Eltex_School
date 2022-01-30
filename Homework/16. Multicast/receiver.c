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
	struct ip_mreqn socket_param;

	socket_param.imr_multiaddr.s_addr = inet_addr(M_ADDR);
	socket_param.imr_address.s_addr = INADDR_ANY;
	socket_param.imr_ifindex = 0;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &socket_param, sizeof(struct ip_mreqn)) == -1)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	memset(&server, 0, sizeof(server));
	
	server.sin_family = AF_INET;  
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(M_PORT);
	
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
