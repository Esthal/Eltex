#include "../FileEditor.h"

void next_line(LINE *cur)
{
    LINE *temp;
    temp = malloc(sizeof(LINE));
    temp->line = (char *)malloc(sizeof(char));
    temp->line[0] = '\0';
    temp->size = 0;
    temp->next = NULL;
    temp->prev = cur;
    cur->next = temp;
}