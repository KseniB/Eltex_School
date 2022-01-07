#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Ствол (Родит.проц.)                    [p1 trunk]
                                      /        \
Ветви (Доч.проц.)               [p2 branch]  [p3 branch]
                                 /       \           \
Листья (Потом.доч.проц.)    [p4 leaves] [p5 leaves]  [p6 leaves]
*/

int main()
{
    pid_t branchPid[2];
    pid_t leavesPid[2];
    /*Переменная для получения двух потомком в первой ветви и одного во второй:*/
    int population = 2;
    int index = 1;
    
    printf(" p%d Trunk   PID:%d\n", index, getpid());

    for (int branch_i = 0; branch_i < 2; branch_i++)
    {
        index++;
        if ((branchPid[branch_i] = fork()) == 0)
        {
            printf("\tp%d Branch  PPID:%d PID:%d\n", index, getppid(), getpid());
            index++;
            if (branch_i == 1){
                index++;
            }
            
            for (int leaves_i = 0; leaves_i < population; leaves_i++)
            {
                index++;
                if ((leavesPid[leaves_i] = fork()) == 0)
                {
                    printf("\t\tp%d Leaves  PPID:%d PID:%d\n", index, getppid(), getpid());
                    
                    return 0;
                }
                waitpid(leavesPid[leaves_i], NULL, WUNTRACED);
            }
            
            return 0;
        }
        waitpid(branchPid[branch_i], NULL, WUNTRACED);
        population--;
    }
    
    return 0;
}
