#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

unsigned char* str_get(unsigned int* len)
{
	*len = 0;
	unsigned int cap = 1;
	unsigned char* str = (unsigned char*) malloc(10 * sizeof(unsigned char));
	unsigned char  ch = getchar();

	while (ch != '\n')
	{
		str[(*len)++] = ch;
		if (*len >= 10)
		{
			cap *= 2;
			str = (unsigned char*) realloc(str, cap * sizeof(unsigned char));
		}
		ch = getchar();
	}
	
	str[*len] = '\0';
	return str;
}

int main(void)
{
    pid_t pid;
    int fd[2];
    int rv;
    
    pid = fork();   
    if (pid == 0)
    {
        int f_w = open("writefile.txt", O_WRONLY|O_APPEND, 0644);
        if (f_w < 0)
        {
            perror("OPEN writefile.txt");
            exit(EXIT_FAILURE);
        }
        
        printf("Enter word:\n");
        unsigned int str_len = 50;
        
        if (pipe(fd) < 0)
        {
            perror("Pipe error");
        }
        
        dup2(f_w, 1);
        unsigned char* str = str_get(&str_len);
        printf("%s\n", str);
        exit(rv);
    }
    else
    {
        wait(&rv);
        int f_r = open("writefile.txt", O_RDONLY);
        
        if (f_r < 0)
        {
            perror("READ writefile.txt");
            exit(EXIT_FAILURE);
        }
        
        unsigned char buf[1];
        size_t byte_r;
        printf("READ FILE:\n");
        
        while ((byte_r = read(f_r, buf, 1)) > 0)
        {
            printf("%c", buf[0]);
        }
    }
    
    close(fd[0]);
    close(fd[1]);
    return 0;
}
