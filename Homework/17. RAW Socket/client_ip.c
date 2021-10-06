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

struct package{
	char network[20];
	char udphdr[8];
	char msg[100];
};

struct iphdr{
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

struct udphdr{
    u_short	uh_sport;		// Source port 
	u_short	uh_dport;		// Destination port
	u_short	uh_ulen;		// Length
	u_short	uh_sum;			// Checksum
};


int main(int argc, char *argv[]){
    
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
	ip_hdr->s_ip = inet_addr("127.0.0.1");
	ip_hdr->d_ip = inet_addr("127.0.0.1");

	header = (struct udphdr*)&buffer[20];
	header->uh_sport = htons(S_PORT);
	header->uh_dport = htons(PORT);
	header->uh_ulen  = htons(SIZE_PACKAGE - 20);
	header->uh_sum   = htons(0);

	strcat(&buffer[28], argv[1]);
	client.sin_family    = AF_INET;  
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(S_PORT);

	if((fd1 = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		perror("Socket:");
		exit(1);
	}
	if(bind(fd1, (struct sockaddr*)&client, sizeof(client)) == -1){
		perror("Bind");
		exit(1);
	}
    if((fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1){
        perror("Socket:");
        exit(1);
    }
    if(setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &(int){1}, sizeof(int)) == -1){
	    perror("Setsockopt");
	    exit(1);
  	}
	memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;  
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

	len = sizeof(server);
	if(sendto(fd, buffer, SIZE_PACKAGE, 0, (struct sockaddr*)&server, len) == -1){
        perror("Sendto:");
        exit(1);
 	}
 	receive = (struct package*)buffer;
	dport = (short *)&receive->udphdr[2];
 	while(1){
		if(recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server, &len) == -1){
		    perror("Recvfrom:");
		    exit(1);
		}
		if(ntohs(*dport) == S_PORT) {
			printf("It's mine: ");
			printf("%s\n", receive->msg);
		}else{
			printf("That's not mine: ");
			printf("%s\n", receive->msg);
		}
	}
}
