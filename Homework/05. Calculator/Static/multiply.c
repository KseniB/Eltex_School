#include "mycalc.h"

float multiply(float pro)
{
	float buf = 0;
	system("clear");
	printf("  +  -  *  /\n");
	printf("       ---\n");
	printf("%.4f * ", pro);
	scanf("%f", &buf);
	pro *= buf;
	
	return pro;
}
