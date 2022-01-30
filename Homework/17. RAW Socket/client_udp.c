#include <stdio.h>
#include <string.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>

#define PORT 8080
#define S_PORT 8081
#define SIZE_PACKAGE 128

struct package
{
	char network[20];
	char udphdr[8];
	char msg[100];
};

struct udphdr
{
	u_short	uh_s_port;		// Source port 
	u_short	uh_d_port;		// Destination port
	u_short	uh_len;			// Length
	u_short	uh_chsum;		// Checksum
};

int main()
{
	int fd, fd1;
	char buffer[128];
	int len;
	short *dport;
	
	memset(buffer, 0, 128);
	
	struct sockaddr_in server, client;
	struct udphdr *header;
	struct package *receive;

	header = (struct udphdr*)buffer;
	header->uh_s_port = htons(S_PORT);
	header->uh_d_port = htons(PORT);
	header->uh_len    = htons(SIZE_PACKAGE);
	header->uh_chsum  = htons(0);

	strcat(&buffer[8], argv[1]);
	
	client.sin_family = AF_INET;  
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(S_PORT);

	if ((fd1 = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	if (bind(fd1, (struct sockaddr*)&client, sizeof(client)) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	
    if ((fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
	memset(&server, 0, sizeof(server));
	
    server.sin_family = AF_INET;  
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

	len = sizeof(server);
	
	if (sendto(fd, buffer, SIZE_PACKAGE, 0, (struct sockaddr*)&server, len) == -1)
	{
        perror("sendto");
        exit(EXIT_FAILURE);
 	}
 	
 	receive = (struct package*)buffer;
	dport = (short *)&receive->udphdr[2];
	
 	while (1)
 	{
		if (recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, &len) == -1)
		{
		    perror("recvfrom");
		    exit(EXIT_FAILURE);
		}
		
		if (ntohs(*dport) == S_PORT)
		{
			printf("It's mine: ");
			printf("%s\n", receive->msg);
		}
		else
		{
			printf("That's not mine: ");
			printf("%s\n", receive->msg);
		}
	}
}
