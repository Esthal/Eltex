#include <stdio.h>

int main()
{
	int a = 0x88CCAABB;
	unsigned char byte;
	int this_bytes;

	printf("a = %X\n",a);


	this_bytes = 0x000000FF;

	for(int i = 0; i < 4; i++)
	{
		byte = (a & this_bytes) >> i*8;
		this_bytes <<= 8;
		printf("byte %d = %X\n",i+1,byte);
		
	}
	byte = 0xDD;
	a = (a & 0xFF00FFFF) | (byte << 16);
	printf("Change 3 byte on DD\na = %X", a);
	printf("\n");


	return 0;
}

