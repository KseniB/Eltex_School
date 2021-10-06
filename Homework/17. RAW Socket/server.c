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
#define ADDR "192.168.0.1"


int main(){
    
	char hi[80] = "Hi, ";
	char str[80];
	char buffer[80];
	int fd;
	struct sockaddr_in client, server;
	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		perror("Socket:");
		exit(1);
	}
	
	memset(&server, 0, sizeof(server));
	memset(&client, 0, sizeof(client));
	server.sin_family    = AF_INET;  
  	server.sin_addr.s_addr = INADDR_ANY;
  	server.sin_port = htons(PORT); 

	if(bind(fd, (struct sockaddr*)&server, sizeof(server)) == -1){
		perror("Bind:");
		exit(1);
	}
	
	int len, n;
	len = sizeof(client);
	while(1){
	  	if((n = recvfrom(fd, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr*)&client, &len)) == -1){
			perror("Recvfrom:");
			exit(1);
		}
		
		buffer[n] = '\0';
		printf("%s\n", buffer);
		strcpy(str, hi);
		strcat(str, buffer);
		if(sendto(fd, str, strlen(str), MSG_CONFIRM, (struct sockaddr*)&client, len) == -1){
			perror("Sendto:");
			exit(1);
		}
		
		memset(str, 0, 80);
		memset(buffer, 0, 80);
	}
	return 0;
}
