#include "../FileEditor.h"

void save_file(LINE *head, char *filename)
{
    FILE *file = fopen(filename, "w");     
    while (head != NULL)
    {
        fprintf(file, "%s\n", head->line);
        head = head->next;
    }
    fclose(file);
}