#include "bash.h"

char *read_line(void)
{
    char *line = NULL;
    ssize_t buffer = 0;
    getline(&line, &buffer, stdin);
    return line;
}