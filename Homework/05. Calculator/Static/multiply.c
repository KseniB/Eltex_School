#include "mycalc.h"

float multiply(float pro)
{
	float buf = 0;
	system("clear");
	printf("  +  -  *  /\n");
	printf("       ---\n");
	printf("%.4f * ", pro);
	if (1 != scanf("%f", &buf))
	{
		trashclean();
		system("clear");
		fprintf(stderr, "Invalid input");
		puts("\nPress Enter to return to the menu");
	    getchar();

		return pro;
	}
	pro *= buf;
	
	return pro;
}
