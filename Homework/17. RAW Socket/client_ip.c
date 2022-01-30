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
#define ADDR 127.0.0.1

struct package
{
	char network[20];
	char udphdr[8];
	char msg[100];
};

struct iphdr
{
	char vers_sizeh;
	char hz;
	short size_packege;
	short id;
	short offset;
	char ttl;
	char proto;
	short checksum;
	int s_ip;
	int d_ip;
};

struct udphdr
{
    u_short	uh_s_port;		// Source port 
	u_short	uh_d_port;		// Destination port
	u_short	uh_len;		    // Length
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
	struct iphdr *ip_hdr;

	ip_hdr = (struct iphdr*)buffer;
	ip_hdr->vers_sizeh = 0x45;
	ip_hdr->offset = 0x0040;
	ip_hdr->ttl = 0x40;
	ip_hdr->proto = 0x11;
	ip_hdr->s_ip = inet_addr(ADDR);
	ip_hdr->d_ip = inet_addr(ADDR);

	header = (struct udphdr*)&buffer[20];
	header->uh_s_port = htons(S_PORT);
	header->uh_d_port = htons(PORT);
	header->uh_len    = htons(SIZE_PACKAGE - 20);
	header->uh_chsum  = htons(0);

	strcat(&buffer[28], argv[1]);
	
	client.sin_family = AF_INET;  
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(S_PORT);

	if ((fd1 = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	if (bind(fd1, (struct sockaddr*)&client, sizeof(client)) == -1
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	
    if ((fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &(int){1}, sizeof(int)) == -1)
    {
	    perror("setsockopt");
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
		if (ntohs(*dport) == S_PORT) {
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
