#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 1024
#define CLIENT 100

void *Thr_client(void *val){
    
    int *fd_socket = (int *)val;
    char buffer[BUF_SIZE] = {0};
    while(1){
        if((recv(*fd_socket, buffer, BUF_SIZE, 0)) == -1){
            perror("recv");
            exit(EXIT_FAILURE);  
        }
        if(strncmp(buffer, "Close", BUF_SIZE) == 0){
            printf("Close fd == %d\n", *fd_socket);
            close(*fd_socket);
            *fd_socket = -1;
            pthread_exit(0);
        }
        if((send(*fd_socket, buffer, BUF_SIZE, 0)) == -1){
            perror("send");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", buffer);
    }
}


int main(void){
    
    struct sockaddr_in server_f;
    int fd;
    int server_socket;
    int socket_f;
    int bind_f;
    char buffer[BUF_SIZE];

    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1){
        perror("fd\n");
        exit(EXIT_FAILURE);
    }else{
        printf("Good!\n");
    }

    server_f.sin_family = AF_INET;
    server_f.sin_port = htons(7777);
    server_f.sin_addr.s_addr = htonl(INADDR_ANY);
    bind_f = bind(fd,(struct sockaddr *)&server_f, sizeof(server_f));
    if(bind_f < 0){
        perror("bind");
        return -1;
    }else{
        printf("Bind Good!\n");
    }

    listen(fd,5);
    pthread_t pthread_id[CLIENT] = {0};
    int fd_socket[CLIENT];
    for(int i = 0; i < CLIENT; i ++){
        fd_socket[i] =  accept(fd, NULL, NULL);
        if(fd_socket[i] == -1){
            perror("fd_socket");
            exit(EXIT_FAILURE);
        }

        void *args = (void *)&fd_socket[i];
        if(pthread_create(&pthread_id[i], NULL, Thr_client, args)){
            perror("Error create");
            exit(EXIT_FAILURE);
        } 
    }
    close(fd);
    return 0;
}
