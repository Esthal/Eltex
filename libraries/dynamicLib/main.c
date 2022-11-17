#include <stdio.h>
#include "calc.h"

void print_command()
{
	puts("\n1 - plus\n2 - minus\n3 - divide\n4 - multiply\n5 - exit");
}

int main(int argc, char const *argv[])
{
	int command, one = 0, two = 0;
	
	short is_run = 1;
	
	while(is_run)
	{
		print_command();
		printf("\nEtner the command: ");
		if(scanf("%d", &command) != 1) 
		{
			command = -1;
			scanf("%*[^\n]");
		}
		switch(command){
			case 1:
				printf("\nEtner first number: ");
				if(scanf("%d", &one) != 1) 
				{
					one = 0;
					scanf("%*[^\n]");
				}
				printf("Etner second number: ");
				if(scanf("%d", &two) != 1) 
				{
					two = 0;
					scanf("%*[^\n]");
				}
				printf("answer: %d\n", calc_plus(one, two));
				break;
			case 2:
				printf("\nEtner first number: ");
				if(scanf("%d", &one) != 1) {
					one = 0;
					scanf("%*[^\n]");
				}
				printf("Etner second number: ");
				if(scanf("%d", &two) != 1) 
				{
					two = 0;
					scanf("%*[^\n]");
				}
				printf("answer: %d\n", calc_minus(one, two));
				break;
			case 3:
				printf("\nEtner first number: ");
				if(scanf("%d", &one) != 1) 
				{
					one = 0;
					scanf("%*[^\n]");
				}
				printf("Etner second number: ");
				if(scanf("%d", &two) != 1) 
				{
					two = 0;
					scanf("%*[^\n]");
				}
				printf("answer: %d\n", calc_divide(one, two));
				break;
			case 4:
				printf("\nEtner first number: ");
				if(scanf("%d", &one) != 1) 
				{
					one = 0;
					scanf("%*[^\n]");
				}
				printf("Etner second number: ");
				if(scanf("%d", &two) != 1) 
				{
					two = 0;
					scanf("%*[^\n]");
				}
				printf("answer: %d\n", calc_multiply(one, two));
				break;
			case 5:
				is_run = 0;
				puts("Good bye!");
				break;
			default:
				break;
				
		}
	}
	return 0;
}