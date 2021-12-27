#include "mycalc.h"

float plus(float sum)
{
	float buf = 0;
	system("clear");
	printf("  +  -  *  /\n");
	printf(" ---\n");
	printf("%.4f + ", sum);
	if (1 != scanf("%f", &buf))
	{
		trashclean();
		system("clear");
		fprintf(stderr, "Invalid input");
		puts("\nPress Enter to return to the menu");
	    getchar();

		return sum;
	}
	sum += buf;
	
	return sum;
}
