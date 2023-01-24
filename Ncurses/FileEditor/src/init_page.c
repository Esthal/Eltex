#include "../FileEditor.h"

void init_page(LINE **head, char *filename)
{
    FILE *file = fopen(filename, "wr");
    fclose(file);

    *head = malloc(sizeof(LINE));
    (*head)->line = (char *)malloc(sizeof(char));
    (*head)->line[0] = '\0';
    (*head)->size = 0;
    (*head)->next = NULL;
    (*head)->prev = NULL;
}