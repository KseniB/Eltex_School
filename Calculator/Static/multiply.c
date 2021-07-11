#include "mycalc.h"

float multiply(float Pro) {
	float a;
	printf("%.4f * ", Pro);
	scanf("%f", &a);
	Pro *= a;
	return Pro;
}
