#include <stdio.h>
#include <string.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>

#define B_PORT 8080
#define ADDR "192.168.0.1"
#define STR_LEN 80

int main()
{
	char hi[STR_LEN] = "Hi, ";
	char str[STR_LEN];
	char buffer[STR_LEN];
	int fd;
	
	struct sockaddr_in client, server;
	
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	memset(&server, 0, sizeof(server));
	memset(&client, 0, sizeof(client));
	
	server.sin_family = AF_INET;  
  	server.sin_addr.s_addr = INADDR_ANY;
  	server.sin_port = htons(B_PORT); 

	if (bind(fd, (struct sockaddr*)&server, sizeof(server)) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	
	int len, n;
	len = sizeof(client);
	
	while (1)
	{
	  	if ((n = recvfrom(fd, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr*)&client, &len)) == -1)
	  	{
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}
		
		buffer[n] = '\0';
		printf("%s\n", buffer);
		strcpy(str, hi);
		strcat(str, buffer);
		
		if (sendto(fd, str, strlen(str), MSG_CONFIRM, (struct sockaddr*)&client, len) == -1)
		{
			perror("sendto");
			exit(EXIT_FAILURE);
		}
		
		memset(str, 0, STR_LEN);
		memset(buffer, 0, STR_LEN);
	}
	
	return 0;
}
