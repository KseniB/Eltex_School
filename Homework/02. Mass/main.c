#include <stdio.h>
#include <string.h>

int exit_t = 0;

/*
    Task 1:
    Вывод поочередных чисел в матрице размером NxN (size_m), 
    начиная с числа К (start_num).
*/

void task1()
{
	int size_m = 0;
	int start_num = 0;
	
	printf("\nEnter the size of the matrix: ");
	scanf("%d", &size_m);
		
	printf("\nEnter the starting number: ");
	scanf("%d", &start_num);
		
    int mtx[size_m][size_m];
    
    for (int i = 0; i < size_m; i++)
    {
        for (int j = 0; j < size_m; j++)
        {
            mtx[i][j] = start_num++;
            printf("%3d ", mtx[i][j]);
        }
        puts("\n");
    }
}

/*
    Task 2:
    Вывод поочередно задом наперед N (len) чисел, 
    начиная числом K (start_num).
*/

void task2()
{
	int len = 0;
	int start_num = 0;
	
	printf("\nEnter the line size: ");
	scanf("%d", &len);
		
	printf("\nEnter the starting number: ");
	scanf("%d", &start_num);
	
    int A[len];
    
    for (int i = 0; i < len; i++)
    {
        A[i] = start_num++;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        printf("%d ", A[i]);
    }
    puts("\n");
}

/*
    Task 3:
    Вывод матрицы размера N (size_m), состоящей из нулей и едениц, 
    сменяющихся по диагонали.
*/

void task3()
{
	int size_m = 0;
	
	printf("\nEnter the size of the matrix: ");
	scanf("%d", &size_m);
	
    int A[size_m][size_m];
    
    for (int i = 0; i < size_m; i++)
    {
        for (int j = 0; j < size_m; j++)
        {
            if ((i + j) >= size_m)
            {
                A[i][j] = 1;   
            }
            else
            {
                A[i][j] = 0;
            }
            printf("%d ", A[i][j]);
        }
        puts("\n");
    }
}

/*
    Task 4:
    Вывод поочередных чисел по спирали в матрице размером NxN (size_m), 
    начиная с числа К (start_num).
*/

void task4()
{
    int size_m = 0;
	int start_num = 0;
	
	printf("\nEnter the size of the matrix: ");
	scanf("%d", &size_m);
		
	printf("\nEnter the starting number: ");
	scanf("%d", &start_num);
	
    int A[size_m][size_m];
    int i = 0;
    int j = 0;
    int last_num = size_m * size_m + start_num - 1;
    
    while (start_num <= last_num)
    {
        A[i][j] = start_num;
        
        if (i <= j + 1 && i + j < size_m - 1)
        {
            j++;
        }
        else if (i < j && i + j >= size_m - 1)
        {
            i++;
        }
        else if (i >= j && i + j > size_m - 1)
        {
            j--;
        }    
        else
        { 
            i--;
        }
        start_num++;
    }
    
    for (int i = 0; i < size_m; i++)
    {
        for (int j = 0; j < size_m; j++)
        {
            printf("%4d", A[i][j]);
        }
        puts("\n");
    }
}

/*
    Task 5:
    Вывод магического квадрата, стороны и диагонали которого имеют равную сумму,
    в матрице размером NxN (size_m), начиная с числа К (start_num). 
    N должно быть нечетным.
*/

void task5()
{
    int size_m = 0;
	int start_num = 0;
	
	printf("\nEnter the size of the matrix (the number must be odd): ");
	scanf("%d", &size_m);
		
	printf("\nEnter the starting number: ");
	scanf("%d", &start_num);
	
    int magic_s[size_m][size_m];
    
    memset(magic_s, 0, sizeof(magic_s));

    int i = size_m / 2;
    int j = size_m - 1;
    
    for (int num = start_num; num <= size_m * size_m + start_num;)
    {
        if (i == -1 && j == size_m)
        {
            j = size_m - 2;
            i = 0;
        } 
        else
        {
            if (j == size_m)
            {
                j = 0;
            }
            if (i < 0)
            {
                i = size_m - 1;
            }
        }
        if (magic_s[i][j])
        {
            j -= 2;
            i++;
            continue;
        }
        else
        {
            magic_s[i][j] = num++;
        }
        j++; 
        i--;
    }
    for (i = 0; i < size_m; i++)
    {
        for (j = 0; j < size_m; j++)
        {
            printf("%4d ", magic_s[i][j]);
        }
        puts("\n");
    }
}

/*
    Вывод меню на экран.
*/

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
		    printf("Exiting the program...");
		    exit(0);
	}
}

int main(void)
{
	int task = 0;
	
	while(exit_t != 1)
	{
		printf("Enter the task number, or any other number to exit: ");
		scanf("%d", &task);
		Menu(task);
	}
	
	return 0;
}
