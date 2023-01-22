#include "../phone_book.h"

void find(struct test * directory)
{
	char findName[50];

	scanf("%*[^\n]");
	printf("Enter a name: ");
	scanf("%50s",findName);

	int size = (int)malloc_usable_size(directory)/sizeof(struct test);
	for(int i = 0; i <= size; i++)
	{
		if(i == size)
		{
			puts("Name not found!");
			return;
		}
		if(strcmp(directory->name, findName) == 0)
		{
			break;
		}
		directory++;
	}
	printf("found: %s %s %s\n", directory->name,directory->last_name, directory->phone);
}