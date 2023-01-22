#include "bash.h"

char **split_line(char *line)
{
    int bufsize = 64;
    int position = 0;
    char **words = malloc(bufsize * sizeof(char*));
    char *word;
    
    if (words == NULL) 
    {
        fprintf(stderr, "Error: malloc\n");
        exit(EXIT_FAILURE);
    }

    word = strtok(line, " \t\r\n\a");

    while (word != NULL) 
    {
        words[position] = word;
        position++;
        if (position >= bufsize) 
        {
            bufsize += 64;
            words = realloc(word, bufsize * sizeof(char*));
            if (words == NULL) 
            {
                fprintf(stderr, "Error: realloc\n");
                exit(EXIT_FAILURE);
            }
        }

        word = strtok(NULL, " \t\r\n\a");
    }
    words[position] = NULL;
    return words;
}