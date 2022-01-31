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
	char Eth[14];
	char network[20];
	char udphdr[8];
	char msg[100];
};

struct ethhdr1
{
	char MAC_D[6];
	char MAC_S[6];
	short type;
};

struct iphdr
{
	char vers_sizeh;
	char hz;
	short size_package;
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
	u_short	uh_len;			// Length
	u_short	uh_chsum;		// Checksum
};

short csum(char *buffer)
{
	int tmp = 0;
	int chsum = 0;
	short *ptr;
	
	ptr = (short *)buffer;
	
	for (int i = 0; i < 10; i++)
	{
		chsum = chsum + (*ptr&0x0000ffff);
		ptr++;
	}
	
	for (int i = 0; i < 2; i++)
	{
		tmp = chsum >> 16;
		chsum = chsum&0xffff;
		
		if (tmp > 0)
		{
			chsum = chsum + tmp;
		}
		else
		{
			break;
		}
	}
	chsum = ~chsum;
	return (short *)(chsum&0xffff);
}

int main()
{
	int fd, fd1;
	char buffer[128];
	int len;
	unsigned short *dport;
	
	memset(buffer, 0, 128);
	
	struct sockaddr_in client;
	struct sockaddr_ll server;
	struct udphdr *header;
	struct package *receive;
	struct iphdr *ip_hdr;
	struct ethhdr1 *eth_hdr;
	
	eth_hdr = (struct ethhdr1*)buffer;
	eth_hdr->MAC_D[0] = 0x08;
	eth_hdr->MAC_D[1] = 0x00;
	eth_hdr->MAC_D[2] = 0x27;
	eth_hdr->MAC_D[3] = 0x32;
	eth_hdr->MAC_D[4] = 0x51;
	eth_hdr->MAC_D[5] = 0x86;
	eth_hdr->MAC_S[0] = 0x08;
	eth_hdr->MAC_S[1] = 0x00;
	eth_hdr->MAC_S[2] = 0x27;
	eth_hdr->MAC_S[3] = 0x3b;
	eth_hdr->MAC_S[4] = 0x36;
	eth_hdr->MAC_S[5] = 0xc8;
	eth_hdr->type = htons(0x0800);

	ip_hdr = (struct iphdr*)&buffer[14];
	ip_hdr->vers_sizeh = 0x45;
	ip_hdr->size_package = htons(SIZE_PACKAGE - 14);
	ip_hdr->id = htons(0x1234);
	ip_hdr->offset = htons(0x4000);
	ip_hdr->ttl = 0x40;
	ip_hdr->proto = 0x11;
	ip_hdr->s_ip = inet_addr("172.21.0.222");
	ip_hdr->d_ip = inet_addr("172.21.0.223");
	ip_hdr->checksum = csum(&buffer[14]);

	header = (struct udphdr*)&buffer[34];
	header->uh_s_port = htons(S_PORT);
	header->uh_d_port = htons(PORT);
	header->uh_len    = htons(SIZE_PACKAGE - 34);
	header->uh_chsum  = htons(0);

	strcat(&buffer[42], argv[1]);
	
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
	
    if ((fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
    {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	memset(&server, 0, sizeof(server));
	
    server.sll_family = AF_PACKET;
    server.sll_ifindex = if_nametoindex("enp0s8");
    server.sll_halen = 6;

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
		
		printf("%d\n", ntohs(*dport));
		
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
