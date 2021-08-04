#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fcntl.h>          
#include <sys/stat.h>


#define B_PORT 7777
#define B_ADDRES "224.0.0.1"

int main(){

char buffer[80] = "broadcast msg";
int fd;
int len;
    
struct sockaddr_in server;

if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
	perror("Socket:");
	exit(1);
}
if(setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &(int){1}, sizeof(int)) == -1) {
	perror("setsockopt");
	exit(1);
}
memset(&server, 0, sizeof(server));
server.sin_family    = AF_INET;  
server.sin_addr.s_addr = inet_addr(B_ADDRES);
server.sin_port = htons(B_PORT); 
len = sizeof(server);

if(sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr*)&server, len) == -1) {
	perror("Sendto:");
	exit(1);
}
    
return 0;
}
