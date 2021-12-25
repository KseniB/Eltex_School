#include "mycalc.h"

float minus(float razn)
{
	float buf = 0;
	system("clear");
	printf("  +  -  *  /\n");
	printf("    ---\n");
	printf("%.4f - ", razn);
	scanf("%f", &buf);
	razn -= buf;
	
	return razn;
}
