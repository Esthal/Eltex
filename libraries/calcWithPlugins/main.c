#include <stdio.h>
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>

struct list_of_func
{
	void *handle;
	char func_name[100];
	char lable[100];
	struct list_of_func *next;
};



void add(struct list_of_func **HEAD, char **func_name, char **lable, void **handle)
{
	struct list_of_func *temp = malloc(sizeof(struct list_of_func));
	strcat(temp->func_name, *func_name);
	strcat(temp->lable, *lable);
	temp->handle = *handle;

	if (*HEAD == NULL)
	{
		*HEAD = temp;
	}
	else
	{
		struct list_of_func *cur = *HEAD;
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = temp;
	}
	
}
void print_list(struct list_of_func *HEAD)
{
	int i = 1;
	printf("Command list:\n");
	printf("0: Exit\n");
	while (HEAD != NULL)
	{
		printf("%d: %s\n", i, HEAD->lable);
		i++;
		HEAD = HEAD->next;
	}
	
	
}

void doing_command(struct list_of_func *HEAD, int command)
{
	for (int i = 1; i < command; i++)
	{
		if (HEAD == NULL)
		{
			printf("Command not found!\n");
			return;
		}
		HEAD = HEAD->next;
		
	}
	int one;
	int two;
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

	int (*func)(int,int);

	func = dlsym(HEAD->handle, HEAD->func_name);


	printf("answer: %d\n\n", func(one,two));
	
}

void close_dl(struct list_of_func *HEAD)
{
	while (HEAD != NULL)
	{
		dlclose(HEAD->handle);
		HEAD = HEAD->next;
	}
}

int init(struct list_of_func **HEAD)
{
	DIR *dp;

	void *handle;
	char **func_name;
	char **lable;
	char path[300];


	dp = opendir("plug");
	if (dp != NULL)
	{
		struct dirent *file;


		while (file = readdir(dp))
		{
			if (strstr(file->d_name, ".so"))
			{
				handle = NULL;
				func_name = NULL;
				memset(path, 0, 300);
				
				strcat(path, "plug/");
				strcat(path, file->d_name);

				handle = dlopen(path, RTLD_LAZY);

				if(!handle)
				{
					fprintf(stderr, "dlopen() error %s\n", dlerror());
					return 1;
				}

				func_name = dlsym(handle, "func_name");
				lable = dlsym(handle, "lable");

				add(&(*HEAD), func_name, lable, &handle);

			}
			
		}
		closedir(dp);
	}
	return 0;
}


int main(int argc, char const *argv[])
{
	struct list_of_func *HEAD = NULL;
	int command;

	if (init(&HEAD) == 1)
	{
		return 1;
	}
	
	while(1)
	{
		print_list(HEAD);
		printf("\nEtner the command: ");
		if(scanf("%d", &command) != 1) 
		{
			command = -1;
			scanf("%*[^\n]");
			continue;
		}
		if (command == 0)
		{
			puts("Good bye!");
			return 0;
		}
		doing_command(HEAD, command);
	}
	close_dl(HEAD);

	return 0;
}