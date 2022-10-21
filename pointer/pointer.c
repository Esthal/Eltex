#include <stdio.h>


int main()
{
	int a = 0x88DDAACC;
	printf("a = %X\n", a);
	char* ptr;
	ptr = (char *)&a;
	ptr+=2;
	*ptr = 0xff;
	printf("a = %X\n", a);
	
	char A = 'A';
	char B = 'B';
	char *ptr1 = &A;
	char **ptr2 = &ptr1;
	printf("ptr2 = %c\n", **ptr2);
	*ptr2 = &B;
	printf("ptr2 = %c\n", **ptr2);
	return 0;
}
