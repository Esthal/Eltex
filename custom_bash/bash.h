#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *read_line(void);
char **split_line(char *line);
void execute(char **split_row);