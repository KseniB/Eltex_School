#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <linux/limits.h>

int main()
{
    char cwd[PATH_MAX] = {0};
    char command[ARG_MAX] = {0};
    char *arg_list1[100] = {0};
    char *arg_list2[100] = {0};
    char *char_position;
    char *token;
    char args_amount = '1';

    pid_t pid[2];
    int i;
    int fd[2];

    printf("Type 'quit' to exit\n\n");
    while (1)
    {
        getcwd(cwd, PATH_MAX);
        printf("%s> ", cwd);
        fgets(command, ARG_MAX, stdin);
        char_position = strchr(command, '\n');
        *char_position = '\0';

        if (strcmp(command, "quit") == 0)
        {
            printf("Quiting...\n");
            exit(0);
        }
        if (command[0] == '\0')
        {
            continue;
        }

        if ((*arg_list1 = strtok(command, "|")) != NULL)
        {
            args_amount = '1';
            token = (strtok(NULL, "|"));

            if (token != NULL)
            {
                token++;
                *arg_list2 = token;
                args_amount = '2';
            }
        }

        char_position = *arg_list1;
        i = 1;
        while (*char_position != '\0')
        {
            if ((*char_position == ' ') && (((*char_position) + 1) != ' '))
            {
                *char_position = '\0';
                arg_list1[i] = char_position + 1;
                i++;
            }
            char_position++;
        }

        if (args_amount == '2')
        {
            arg_list1[i - 1] = NULL;
            char_position = *arg_list2;
            i = 1;
            while (*char_position != '\0')
            {
                if (*char_position == ' ')
                {
                    *char_position = '\0';
                    arg_list2[i] = char_position + 1;
                    i++;
                }
                char_position++;
            }
            pipe(fd);
        }

        if ((pid[0] = fork()) == 0)
        {
            if (args_amount == '2')
            {
                while (dup2(fd[1], 1) == -1){}
                close(fd[0]);
                close(fd[1]);
            }
            if (execvp(*arg_list1, arg_list1) == -1)
            {
                perror("EXECUTION 1: ");
                return -1;
            }
        }
        if (args_amount == '2')
        {
            if ((pid[1] = fork()) == 0)
            {
                while (dup2(fd[0], 0) == -1) {}
                close(fd[0]);
                close(fd[1]);

                if (execvp(*arg_list2, arg_list2) == -1)
                {
                    perror("EXECUTION 2: ");
                    return -1;
                }
            }
        }

        waitpid(pid[0], NULL, WUNTRACED);
        memset(arg_list1, 0, sizeof(arg_list1));

        if (args_amount == '2')
        {
            waitpid(pid[1], NULL, WNOHANG);
            memset(arg_list2, 0, sizeof(arg_list2));
            close(fd[0]);
            close(fd[1]);
        }
    }
    
    return 0;
}
