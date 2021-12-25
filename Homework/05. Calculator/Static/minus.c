#include "mycalc.h"

float minus(float razn)
{
	float buf = 0;
	system("clear");
	printf("  +  -  *  /\n");
	printf("    ---\n");
	printf("%.4f - ", razn);
	if (1 != scanf("%f", &buf))
	{
		trashclean();
		system("clear");
		fprintf(stderr, "Invalid input");
		puts("\nPress Enter to return to the menu");
	    getchar();

		return razn;
	}
	razn -= buf;
	
	return razn;
}
