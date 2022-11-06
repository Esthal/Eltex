#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>


struct test{
	char name[51];
	char last_name[51];
	char phone[21];
};


void print_command(void)
{
	puts("\n1 - add\n2 - view\n3 - find\n4 - delete\n5 - exit");
}
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

void add(struct test ** directory)
{
	if(*directory == NULL)
	{
		printf("create\n");
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
		printf("add %d\n",size);
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


int main()
{
	
	
	struct test *directory = NULL;
	

	int command;
	
	short is_run = 1;
	
	while(is_run){
		print_command();

		scanf("%*[^\n]");
		printf("\nEtner the command: ");
		if(scanf("%d", &command) != 1) 
		{
			command = -1;
			scanf("%*[^\n]");
		}
		switch(command)
		{
			case 1:
				add(&directory);
				break;
			case 2:
				view(directory);
				break;
			case 3:
				find(directory);
				break;
			case 4:

				scanf("%*[^\n]");
				printf("Etner record number (-1 to delete all): ");
				if(scanf("%d", &command) != 1) 
				{
					command = -1;
					scanf("%*[^\n]");
					break;
				}
				delete(&directory, command);
				break;
			case 5:
				is_run = 0;
				puts("Good bye!");
				break;
			default:
				puts("Unknow command");
				break;
			
		}
		
	}	
	free(directory);
	return 0;
}

