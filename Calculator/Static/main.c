#include "mycalc.h"

void menu(float Res) {
  printf("1. + \n");
  printf("2. - \n");
  printf("3. * \n");
  printf("4. / \n");
  printf("5. Reset \n");
  printf("6. Exit \n");
  printf("--------------\n");
  printf("Result = %.2f\n", Res);
  printf("--------------\n");
}

int main() {
	float res = 0.0;
	char a[255];
	int b;
	while(1) {
		system("clear");
		menu(res);
		fgets(&a, 2, stdin);
    fflush(stdin);
		b = atoi(&a);
		switch(b) {
			case 1:
				res = plus(res);
				break;
			case 2:
				res = minus(res);
          break;
			case 3:
				res = multiply(res);
          break;
			case 4:
				res = divide(res);
          break;
			case 5:
				res = 0.0;
          break;
			case 6:
				_Exit(0);
          break;
			default :
				printf("Wrong input \n");
				  break;
		}
	}
}
