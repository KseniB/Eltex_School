#include "lib/mycalc.h"

int main(){
	float result = 0;
	char buf = 0;
	do{
		system("clear");
		menu(result);
		if (1 != scanf("%c", &buf))
		{
			trashclean();
			system("clear");
			fprintf(stderr, "Invalid input");
			puts("\nPress Enter to return to the menu");
			getchar();
	
			return -1;
		}
		
		if (buf == '+')
		{
				result = plus(result);
		}
		else if (buf == '-')
		{
			result = minus(result);
		}
		else if (buf == '*')	
		{
			result = multiply(result);
		}
		else if (buf == '/')		
		{
			result = divide(result);
		}
		else if (buf == '1')		
		{
			result = 0;
		}
		else if (buf == '2')		
		{
			system("clear");
			puts("Exiting the program...");
			exit(0);
		}
	}while(1);
	
	return 0;
}
