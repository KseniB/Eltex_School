#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <pthread.h>

#define SERVER_CHAT_QUEUE "/server_chat"
#define SERVER_SERVICE_QUEUE "/server_service"
#define MSG_BUF_SIZE 100
#define MSGS_AMOUNT 10

struct list
{
    unsigned int pid[10];
    unsigned int clients_amount;
    mqd_t chat_descriptor;
    mqd_t service_descriptor;
    mqd_t client_descriptor[10];
};

struct mq_attr queueAttr;

void *check_service(void *params_ptr)
{
    struct list *params = params_ptr;
    char inbox[MSG_BUF_SIZE];
    char new_descriptor[20];

    while (1)
    {
        if (mq_receive(params->service_descriptor, inbox, MSG_BUF_SIZE, NULL) > 0)
        {
            printf("[SERVICE] - Recieved new pid: %s\n", inbox);
            params->pid[params->clients_amount] = atoi(inbox);
            sprintf(new_descriptor, "/client_%d", params->pid[params->clients_amount]);
            
            while ((params->client_descriptor[params->clients_amount] = mq_open(new_descriptor, O_WRONLY | O_CREAT, 0777, &queueAttr)) == -1){}
            printf("[SERVICE] - Client_%d queue created\n", params->pid[params->clients_amount]);
            params->clients_amount++;
        }
    }
}

void *check_chat(void *params_ptr)
{
    struct list *params = params_ptr;
    char inbox[MSG_BUF_SIZE];

    while (1)
    {
        if (mq_receive(params->chat_descriptor, inbox, MSG_BUF_SIZE, NULL) > 0)
        {
            for (int i = 0; i < params->clients_amount; i++)
            {
                while (mq_send(params->client_descriptor[i], inbox, strlen(inbox), 0) != 0){}
            }
            printf("[CHAT] - Forwarded received msg from (%s) to a clients queues\n", strtok(inbox, ":"));
            memset(inbox, 0, sizeof(inbox));
        }
    }
}

void *check_input()
{
    char input[MSG_BUF_SIZE];

    while (1)
    {
        fgets(input, MSG_BUF_SIZE, stdin);
        if (strcmp(input, "/shut\n") == 0)
        {
            pthread_exit(NULL);
        }
    }
}


int main()
{
    struct list params;
    pthread_t check_service_tid, check_chat_tid, check_input_tid;
    char new_descriptor[20];

    pthread_attr_t threadAttr;
    pthread_attr_init(&threadAttr);
    pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);

    queueAttr.mq_flags = 0;
    queueAttr.mq_maxmsg = MSGS_AMOUNT;
    queueAttr.mq_msgsize = MSG_BUF_SIZE;
    queueAttr.mq_curmsgs = 0;

    params.clients_amount = 0;

    printf("[SERVER] - Started\n");
    while ((params.chat_descriptor = mq_open(SERVER_CHAT_QUEUE, O_RDONLY | O_CREAT, 0777, &queueAttr)) == -1){}
    printf("[SERVER] - Chat queue created\n");
    while ((params.service_descriptor = mq_open(SERVER_SERVICE_QUEUE, O_RDONLY | O_CREAT, 0777, &queueAttr)) == -1){}

    while (pthread_create(&check_service_tid, &threadAttr, check_service, (void *)&params) != 0){}
    while (pthread_create(&check_chat_tid, &threadAttr, check_chat, (void *)&params) != 0){}
    while (pthread_create(&check_input_tid, &threadAttr, check_input, NULL) != 0){}

    pthread_join(check_input_tid, NULL);
    pthread_cancel(check_service_tid);
    pthread_cancel(check_chat_tid);

    while (mq_close(params.chat_descriptor) == -1){}
    while (mq_unlink(SERVER_CHAT_QUEUE) == -1){}
    
    printf("[SERVER] - Chat queue closed and unlinked\n");
    while (mq_close(params.service_descriptor) == -1){}
    while (mq_unlink(SERVER_SERVICE_QUEUE) == -1){}

    for (int i = 0; i < params.clients_amount; i++)
    {
        while (mq_close(params.client_descriptor[i]) == -1){}
        sprintf(new_descriptor, "/client_%d", params.pid[i]);
        
        while (mq_unlink(new_descriptor) == -1){}
        printf("[SERVER] - Client_%d queue closed and unlinked\n", params.pid[i]);
    }

    printf("[SERVER] - Shuted down\n");
    exit(0);
}
