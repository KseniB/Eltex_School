#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t BitShift(uint32_t Number, uint8_t BS){
	Number|=(0xFF<<(BS*8));
	return Number;
}

int main(void){
	uint32_t Num;
	uint32_t Shift;

	printf("Your number in bytes (0xXXXXXXXX):");
	scanf("%x", &Num);
	printf("How many bytes to shift (0-3):");
	scanf("%d", &Shift);

	printf("Result: %x \n", BitShift(Num, (uint8_t)Shift));

	return 0;
}
