#include "mycalc.h"

float divide(float Del){
	float a;
	do{
		printf("%.4f / ", Del);
		scanf("%f", &a);
		if( a == 0) {
			printf("Wrong input \n");
		}else{
			Del /= a;
			return Del;
		}
	}while(a == 0);
}
