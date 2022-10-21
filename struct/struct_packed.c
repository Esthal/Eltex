#include <stdio.h>

int main(){
	struct test
	{
		char a;
		int b;
	} __attribute__((packed));
	char mass[10] = {'A',2,0,0,0,'B',1,0,0,0};
	
	struct test* my_test = (struct test*)mass;
	
	printf("char = %c    int = %d\n",my_test->a, my_test->b);
	my_test++;
	printf("char = %c    int = %d\n",my_test->a, my_test->b);
	
	return 0;
}
