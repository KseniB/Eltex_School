#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define SHOP 5
#define BUYER 3
#define LOADER_ADD 200
#define NEED_MIN 9700
#define NEED_RANGE 600

int Shop[SHOP] = {0};
int f_end = 0;

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx3 = PTHREAD_MUTEX_INITIALIZER;

void *buyer(void *val){

    int need = NEED_MIN + rand( )% NEED_RANGE;
    int i = 0;
    int num_buyer = *((int*)val);
    while(need > 0){
        for(int i = 0; i < SHOP; i++){
            pthread_mutex_lock(&mtx1);
            if(Shop[i] != 0){
                need -= Shop[i];
                printf("Buyer - [%d]: buy: %d need more: %d\n", num_buyer, Shop[i], need);
                Shop[i] = 0;
            }
            pthread_mutex_unlock(&mtx1);
        }
        sleep(1);
    }
    pthread_mutex_lock(&mtx2);
    f_end++;
    printf("Buyer [%d] exits\n", num_buyer);
    pthread_mutex_unlock(&mtx2);
}

void *loader(void *val){
    
    int i = 0;
    while(f_end < BUYER){
        pthread_mutex_lock(&mtx3);
        i = rand() % 4;
        printf("Loader +%d in %d\n", LOADER_ADD, i);
        Shop[i] += LOADER_ADD; 
        printf("Shop:[%d][%d][%d][%d][%d]\n", Shop[0], Shop[1], Shop[2], Shop[3], Shop[4]);
        pthread_mutex_unlock(&mtx3);
        sleep(2);
    }
    printf("Work is done.\n");
}


int main(void){
    
    srand(time(NULL));
    pthread_t tid_buyer[BUYER];
    pthread_t tid_loader;
    pthread_create(&tid_loader, NULL, loader, NULL);
    for(int i = 0; i < BUYER; i++){
        pthread_create(&tid_buyer[i], NULL, buyer, &i);
    }
    
    pthread_join(tid_loader, NULL);
    for(int i = 0; i < BUYER; i++){
        pthread_join(tid_buyer[i], NULL);
    }
}
