#include "mycalc.h"

float plus(float Sum){
	float a;
	printf("%.4f + ", Sum);
	scanf("%f", &a);
	Sum += a;
	return Sum;
}
