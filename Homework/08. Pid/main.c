#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Ствол (Родит.проц.)                [p1 trunk]
                                  /        \
Ветви (Доч.проц.)           [p2 branch]  [p3 branch]
                            /       \           \
Листья (Доч.проц.)    [p4 leaves] [p5 leaves]  [p6 leaves]
*/

int main(){
  
    pid_t branchPid[2];
    pid_t leavesPid[2];
    int branch_i;
    int leaves_i;
    int population = 2;
  
    for (branch_i = 0; branch_i < 2; branch_i++){
        if ((branchPid[branch_i] = fork()) == 0){
            for (leaves_i = 0; leaves_i < population; leaves_i++){
                if ((leavesPid[leaves_i] = fork()) == 0){
                    printf("Leaves  PPID:%d PID:%d\n", getppid(), getpid());
                    return 0;
                }
            waitpid(leavesPid[leaves_i], NULL, WUNTRACED);
            }
        printf("Branch  PPID:%d PID:%d\n", getppid(), getpid());
        return 0;
        }
    waitpid(branchPid[branch_i], NULL, WUNTRACED);
    population--;
    }
    printf("Trunk   PID:%d\n", getpid());
    return 0;
}
