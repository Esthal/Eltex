#include "phone_book.h"

int main()
{
	struct test *directory = NULL;
	int command;
	short is_run = 1;
	
	while(is_run){
		print_command();

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

