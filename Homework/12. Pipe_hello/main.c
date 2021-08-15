#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(void){
    
    int rdwr[2] = {0};
    char r_buf = 0;
    char hello[6] = "Hello";
    if(pipe(rdwr) == -1){
        exit(EXIT_FAILURE);
    }
    
    pid_t child = fork();
    if(child == -1){
        exit(EXIT_FAILURE);
    }
    if(child == 0){
        close(rdwr[1]);
        printf("Child: ");
        while(read(rdwr[0], &r_buf, 1)){
            printf("%c",r_buf);
        }
        close(rdwr[0]);
        exit(EXIT_SUCCESS);
    }else{
        printf("Parent write\n");
        close(rdwr[0]);
        write(rdwr[1], hello, 6);
        close(rdwr[1]);
        exit(EXIT_SUCCESS);
    }
}
