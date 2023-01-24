#include "../phone_book.h"

void view(struct test *directory)
{
	int size = (int)malloc_usable_size(directory)/sizeof(struct test);

	printf("Directory: %d\n", size);
	for(int i = 0; i < size; i++)
	{
		printf("%d - %s %s %s\n",i,directory->name,directory->last_name, directory->phone);
		directory++;
	}
	printf("\n");
}