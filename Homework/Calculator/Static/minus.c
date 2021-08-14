#include "mycalc.h"

float minus(float Raz){
	float a;
	printf("%.4f - ", Raz);
	scanf("%f", &a);
	Raz -= a;
	return Raz;
}
