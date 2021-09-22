#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

unsigned char* Str_get(unsigned int* l){
    
	*l = 0;
	unsigned int cap = 1;
	unsigned char* s = (unsigned char*) malloc(10 * sizeof(unsigned char));
	unsigned char  c = getchar();

	while(c != '\n'){
		s[(*l)++] = c;
		if(*l >= 10){
			cap *= 2;
			s = (unsigned char*) realloc(s, cap * sizeof(unsigned char));
		}
		c = getchar();
	}
	s[*l] = '\0';
	return s;
}

int main(void){
    
    pid_t _pid;
    int rv;
    int fid[2];
    _pid = fork();
    
    if(_pid == 0){
        int f_w = open("writefile.txt", O_WRONLY|O_APPEND, 0644);
        if(f_w < 0){
            perror("OPEN writefile.txt");
            exit(EXIT_FAILURE);
        }
        printf("Enter word\n");
        unsigned int g = 50;
        if(pipe(fid) < 0){
            perror("Pipe error");
        }
        dup2(f_w, 1);
    
        unsigned char* str = Str_get(&g);
        printf("%s\n", str);
        exit(rv);
    }else{
        wait(&rv);
        int f_r = open("writefile.txt", O_RDONLY);
        if(f_r < 0){
            perror("READ writefile.txt");
            exit(EXIT_FAILURE);
        }
        unsigned char buf[1];
        size_t byte_r;
        printf("READ FILE:\n");
        while((byte_r = read(f_r, buf, 1)) > 0){
            printf("%c", buf[0]);
        }
    }
  
    return 0;
}
