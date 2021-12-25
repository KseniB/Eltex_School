#include "mycalc.h"

float divide(float del)
{
	float buf = 0;
	system("clear");
	printf("  +  -  *  /\n");
	printf("          ---\n");
	printf("%.4f / ", del);
	if (1 != scanf("%f", &buf))
	{
		trashclean();
		system("clear");
		fprintf(stderr, "Invalid input");
		puts("\nPress Enter to return to the menu");
	    getchar();

		return del;
	}
	
	if(buf == 0)
	{
	    trashclean();
		fprintf(stderr, "Invalid input");
        puts("\nPress Enter to return to the menu");
	    getchar();
	    
    	return del;
	}
	else
	{
		del /= buf;
		
		return del;
	}
}
