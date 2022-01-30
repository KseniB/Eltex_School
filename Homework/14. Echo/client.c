#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 1024
#define B_PORT 7777

int main(void)
{
    int fd;
    int connect_f;
    struct sockaddr_in client;
    
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(B_PORT); 
    client.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    
    connect_f = connect(fd, (struct sockaddr *)&client, sizeof(client));
    if (connect_f < 0)
    {
        perror("connect");
        return -1;
    }

    while (1)
    {
        char buffer[BUF_SIZE] = {0};
        printf("Client: ");
		fgets(buffer, BUF_SIZE, stdin);
		
        if ((send(fd, buffer, strlen(buffer) - 1, 0)) == -1)
        {
            perror("send");
            exit(EXIT_FAILURE);
        }
        
        if (strncmp(buffer, "exit", 4) == 0)
        {
            break;
        }
        
        int recv_f = recv(fd, buffer, BUF_SIZE, 0);
        printf("Server: %s", buffer);
        if(recv_f == -1)
        {
            perror("recv");
            exit(EXIT_FAILURE);
        }
    }
    
    close(fd);
    return 0;
}
