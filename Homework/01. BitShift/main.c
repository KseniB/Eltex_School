#include <stdio.h>
#include <stdlib.h>

int bit_shift(int num)
{
    int shift = 0;
	for (int i = 0; i < 4; i++)
    {
        shift = ((num >> i * 8) & 0xFF);
        printf("Byte #%d: 0x%x\n", i, shift);
    }
	return 0;
}

int bit_replace(int num, int shift, int val)
{
    int b_num = 0x00000000;
    
    b_num = (b_num >> shift * 8) ^ 0xFF;
    b_num = (b_num << shift * 8) ^ 0xFFFFFFFF;
    
	num = (num & b_num) ^ (val << shift * 8);
	
	printf("Result: %x \n", num);
	puts("\n");
	
    return 0;
}

int main(void)
{
	unsigned int num = 0;
	unsigned int shift = 0;
	unsigned int val = 0;
	
    while(1){
    	printf("Your number in bytes (0xXXXXXXXX):");
    	scanf("%x", &num);
    	bit_shift(num);
    	
    	printf("Which byte to replace? (0-3):");
    	scanf("%x", &shift);
    	
    	printf("Enter a new byte (0xXX):");
    	scanf("%x", &val);
    	bit_replace(num, shift, val);
    }
	return 0;
}
