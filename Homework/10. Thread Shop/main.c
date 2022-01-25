#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define SHOP 5
#define BUYER 3
#define LOADER_ADD 500
#define SHOP_MIN 950
#define SHOP_MAX 1050
#define NEED_MIN 4500
#define NEED_MAX 5500

int shop[SHOP] = {};
int buy_end = 0;

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx3 = PTHREAD_MUTEX_INITIALIZER;

void *buyer(void *val)
{
    int need = NEED_MIN + rand() % (NEED_MAX - NEED_MIN + 1);
    int num_buyer = *((int*)val);
    
    while (need > 0)
    {
        for (int i = 0; i < SHOP; i++)
        {
            pthread_mutex_lock(&mtx1);
            if (shop[i] != 0)
            {
                if (need > shop[i])
                {
                    need -= shop[i];
                    printf(">Buyer [%d]: buy: %d in shop [%d]  need more: %d\n", num_buyer, shop[i], i, need);
                    shop[i] = 0;
                }
                else
                {
                    shop[i] -= need;
                    need = 0;
                    printf(">Buyer [%d]: buy: %d in shop [%d]  need more: %d\n", num_buyer, shop[i], i, need);
                }
            }
            pthread_mutex_unlock(&mtx1);
        }
        sleep(1);
    }
    pthread_mutex_lock(&mtx2);
    buy_end++;
    printf("----------------\n");
    printf("Buyer [%d] exits\n", num_buyer);
    printf("----------------\n");
    pthread_mutex_unlock(&mtx2);
}

void *loader(void *val)
{
    while (buy_end < BUYER)
    {
        pthread_mutex_lock(&mtx3);
        int i = rand() % 4;
        printf("  Loader +%d in %d\n", LOADER_ADD, i);
        shop[i] += LOADER_ADD; 
        printf("Shop:[%d][%d][%d][%d][%d]\n", shop[0], shop[1], shop[2], shop[3], shop[4]);
        pthread_mutex_unlock(&mtx3);
        sleep(1);
    }
    printf("Work is done.\n");
}


int main(void)
{
    srand(time(NULL));
    pthread_t tid_buyer[BUYER];
    pthread_t tid_loader;
    int num_b[BUYER]= {1, 2, 3};
    
    for (int i = 0; i < SHOP; i++)
    {
        shop[i] = SHOP_MIN + rand() % (SHOP_MAX - SHOP_MIN + 1);
    }
    
    printf("Shop:[%d][%d][%d][%d][%d]\n", shop[0], shop[1], shop[2], shop[3], shop[4]);
    printf("---------------------------------\n");
    
    if (pthread_create(&tid_loader, NULL, loader, NULL) != 0)
    {
        perror("Create");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < BUYER; i++)
    {
        if (pthread_create(&tid_buyer[i], NULL, buyer, &num_b[i]) != 0)
        {
            perror("Create");
            exit(EXIT_FAILURE);
        }
    }
    
    if (pthread_join(tid_loader, NULL) != 0)
    {
        perror("Join");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < BUYER; i++)
    {
        if (pthread_join(tid_buyer[i], NULL) != 0)
        {
            perror("Join");
            exit(EXIT_FAILURE);
        }
    }
}
