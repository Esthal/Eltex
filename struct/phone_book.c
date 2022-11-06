#include <stdio.h>
#include <string.h>


struct test
{
	char name[51];
	char last_name[51];
	char phone[21];
};


void print_command(void)
{
	puts("1 - add\n2 - view\n3 - find\n4 - delete\n5 - exit");
}
void view(struct test *directory)
{
	puts("Directory:");
	for(int i = 0; i < 10; i++)
	{
		printf("%d - %s %s %s\n",i,directory->name,directory->last_name, directory->phone);
		directory++;
	}
	printf("\n");
}
void delete(struct test *directory, int num)
{
	if(num > 9)
	{
		puts("unknow number!");
		return;
	}
	directory += num;
	memset(directory->name, 0, 50);
	memset(directory->last_name, 0, 50);
	memset(directory->phone, 0, 20);
}

void add(struct test *directory)
{
	for(int i = 0; i <= 10; i++)
	{
		if(i == 10)
		{
			puts("directory is full!");
			return;
		}
		if(directory->name[0] == 0) break;
		directory++;
	}
	scanf("%*[^\n]");
	printf("Etner name: ");
	scanf("%50s",directory->name);
	
	scanf("%*[^\n]");
	printf("Etner last last_name: ");
	scanf("%50s",directory->last_name);

	scanf("%*[^\n]");
	printf("Etner phone: ");
	scanf("%20s",directory->phone);

}
void find(struct test * directory)
{
	char findName[50];
	printf("Enter a name: ");
	scanf("%50s",findName);
	
	for(int i = 0; i <= 10; i++)
	{
		if(i == 10)
		{
			puts("Name not found!");
			return;
		}
		if(strcmp(directory->name, findName) == 0)break;
		directory++;
	}
	printf("found: %s %s %s\n", directory->name,directory->last_name, directory->phone);
}


int main()
{
	
	
	struct test directory[10] = {};
	
	strcpy(directory[0].name, "Nick");
	strcpy(directory[0].last_name, "Smith");
	strcpy(directory[0].phone, "79990001111");

	int command;
	
	short is_run = 1;
	
	while(is_run)
	{
		print_command();
		printf("Etner the command: ");
		if(scanf("%d", &command) != 1)
		{
			command = -1;
			scanf("%*[^\n]");
		}
		switch(command){
			case 1:
				add(directory);
				break;
			case 2:
				view(directory);
				break;
			case 3:
				find(directory);
				break;
			case 4:
				printf("Etner record number: ");
				if(scanf("%d", &command) != 1)
				{
					command = -1;
					scanf("%*[^\n]");
					break;
				}
				delete(directory, command);
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
	
	return 0;
}

