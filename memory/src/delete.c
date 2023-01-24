#include "../phone_book.h"

void delete(struct test ** directory, int num)
{
	int size = ((int)malloc_usable_size(*directory)/sizeof(struct test))-1; 
	if(*directory == NULL)
	{
		printf("Empty directory!\n");
		return;
	}
	if(num < -1) 
	{
		printf("Wrong number!\n");
		return;
	}
	if((num > size)&&(num != -1)) 
	{
		printf("Wrong number!\n");
		return;
	}
	if(num == -1)
	{
		free(*directory);
		*directory = NULL;
	}
	else
	{
		memset(((*directory)+num)->name, 0, 51);
		memset(((*directory)+num)->last_name, 0, 51);
		memset(((*directory)+num)->phone, 0, 21);
		
		for(int i = num; i < size; i++)
		{
			strcpy(((*directory)+num)->name, ((*directory)+num+1)->name);
			strcpy(((*directory)+num)->last_name, ((*directory)+num+1)->last_name);
			strcpy(((*directory)+num)->phone, ((*directory)+num+1)->phone);
		}
		*directory = realloc(*directory, malloc_usable_size(*directory)-sizeof(struct test));
	}
}