#include "mycalc.h"

float plus(float sum)
{
	float buf = 0;
	system("clear");
	printf("  +  -  *  /\n");
	printf(" ---\n");
	printf("%.4f + ", sum);
	scanf("%f", &buf);
	sum += buf;
	
	return sum;
}
