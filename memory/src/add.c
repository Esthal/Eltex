#include "../phone_book.h"

void add(struct test ** directory)
{
	if(*directory == NULL)
	{
		if((*directory = malloc(sizeof(struct test))) < 0)
		{
			perror("Out of memory!");
			exit(EXIT_FAILURE);
		}
		scanf("%*[^\n]");
		printf("Etner name: ");
		scanf("%50s",(*directory)->name);

		scanf("%*[^\n]");
		printf("Etner last last_name: ");
		scanf("%50s",(*directory)->last_name);

		scanf("%*[^\n]");
		printf("Etner phone: ");
		scanf("%20s",(*directory)->phone);

	}
	else
	{
		int size = (int)(malloc_usable_size(*directory)/sizeof(struct test));
		if((*directory = realloc(*directory, malloc_usable_size(*directory)+sizeof(struct test))) < 0)
		{
			perror("Out of memory!");
			exit(EXIT_FAILURE);
		}

		scanf("%*[^\n]");
		printf("Etner name: ");
		scanf("%50s",((*directory)+size)->name);

		scanf("%*[^\n]");
		printf("Etner last last_name: ");
		scanf("%50s",((*directory)+size)->last_name);

		scanf("%*[^\n]");
		printf("Etner phone: ");
		scanf("%20s",((*directory)+size)->phone);
	}

}