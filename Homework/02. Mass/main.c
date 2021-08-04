#include <stdio.h>
#include <string.h>

int exit_t = 0;

void task1(){
    
	int N = 3;
    int K = 1;
    int A[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            A[i][j] = K++;
            printf("%3d ", A[i][j]);
        }
        printf("\n");
    }
}

void task2(){
    
	int N = 10;
    int K = 1;
    int A[N];
    for (int i = 0; i < N; i++){
        A[i] = K++;
    }
    for (int i = N - 1; i >= 0; i--){
        printf("%d ", A[i]);
    }
    printf("\n");
}

void task3(){
    
	int N = 5;
    int A[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if ((i + j) >= N){
                A[i][j] = 1;   
            } else {
                A[i][j] = 0;
            }
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

void task4(){
    
    int N = 5;
    int A[N][N];
    int i = 0;
    int j = 0;
    int k = 1;
    while (k <= N*N){
        A[i][j] = k;
        if (i <= j + 1 && i + j < N - 1){
            j++;
        }
        else if (i < j && i + j >= N - 1){
            i++;
        }
        else if (i >= j && i + j > N - 1){
            j--;
        }    
        else{ 
            i--;
        }
        k++;
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%3d", A[i][j]);
        }
        printf("\n");
    }
}

void task5(){
    
    int N = 5; // ширина магического квадрата, должна быть нечетной (task 5)
	int C = 8; // число, с которого начинается магический квадрат (task 5)
    int magicS[N][N];
    memset(magicS, 0, sizeof(magicS));

    int i = N / 2;
    int j = N - 1;
    for (int num = C; num <= N * N + C; ){
        if (i == -1 && j == N){
            j = N - 2;
            i = 0;
        } else{
            if (j == N){
                j = 0;
            }
            if (i < 0){
                i = N - 1;
            }
        }
        if (magicS[i][j]){
            j -= 2;
            i++;
            continue;
        } else{
            magicS[i][j] = num++;
        }
            j++; 
            i--;
        
    }
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            printf("%3d ", magicS[i][j]);
        }
        printf("\n");
    }
}

void Menu(int task)
{
	switch (task)
	{
		case 1:
		task1();
		break;

		case 2:
		task2();
		break;

		case 3:
		task3();
		break;

		case 4:
		task4();
		break;
		
		case 5:
		task5();
		break;
	
		default:
		exit_t = 1;
	}

}

int main(void){
    
	int Task = 0;
	
	while(exit_t != 1){
		printf("Enter number of task:");
		scanf("%d", &Task);
		Menu(Task);
	}
	return 0;
}
