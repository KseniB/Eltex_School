#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <mqueue.h>

#define SERVER_CHAT_QUEUE "/server_chat"
#define SERVER_SERVICE_QUEUE "/server_service"
#define MSG_BUF_SIZE 100

void *check_self_queue(void *param)
{
    mqd_t client_descriptor = *((mqd_t *)param);
    char inbox[MSG_BUF_SIZE];

    while (1)
    {
        if (mq_receive(client_descriptor, inbox, MSG_BUF_SIZE, NULL) > 0)
        {
            printf("%s", inbox);
            memset(inbox, 0, sizeof(inbox));
        }
    }
}


int main()
{
    mqd_t chat_descriptor, service_descriptor, client_descriptor;
    pid_t pid;
    pthread_t check_self_queue_tid;
    
    char input[MSG_BUF_SIZE - 10];
    char message[MSG_BUF_SIZE + 2];
    char nickname[10];
    char self_descriptor[20];
    char *char_position;

    pthread_attr_t threadAttr;
    pthread_attr_init(&threadAttr);
    pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);

    printf("[CLIENT] - Started\n");

    while ((chat_descriptor = mq_open(SERVER_CHAT_QUEUE, O_WRONLY)) == -1){}
    printf("[CLIENT] - Chat queue opened\n");
    while ((service_descriptor = mq_open(SERVER_SERVICE_QUEUE, O_WRONLY)) == -1){}

    pid = getpid();
    sprintf(message, "%d", pid);
    while (mq_send(service_descriptor, message, strlen(message), 0) != 0){}
    while (mq_close(service_descriptor) == -1){}

    printf("Enter your nickname: ");
    fgets(nickname, 10, stdin);
    char_position = strchr(nickname, '\n');
    *char_position = '\0';

    sprintf(self_descriptor, "/client_%d", pid);
    while ((client_descriptor = mq_open(self_descriptor, O_RDONLY)) == -1){}

    while (pthread_create(&check_self_queue_tid, &threadAttr, check_self_queue, (void *)&client_descriptor) != 0){}

    printf("--------CHAT--------\n");
    while (1)
    {
        fgets(input, (MSG_BUF_SIZE - 10), stdin);
        if (strcmp(input, "/shut\n") == 0)
        {
            break;
        }
    }

    while (mq_close(chat_descriptor) == -1){}
    printf("[CLIENT] - Chat queue closed\n");
    while (mq_close(client_descriptor) == -1){}

    printf("[CLIENT] - Shuted down\n");
    exit(0);
}
