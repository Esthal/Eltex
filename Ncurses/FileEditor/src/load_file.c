#include "../FileEditor.h"

void load_file(LINE **head, char *filename, int max_size_line, int *lines_count)
{
    FILE *file = fopen(filename, "r");
    char buffee[max_size_line];

    *head = malloc(sizeof(LINE));
    (*head)->line = (char *)malloc(sizeof(char));
    (*head)->line[0] = '\0';
    (*head)->size = 0;
    (*head)->next = NULL;
    (*head)->prev = NULL;

    LINE *cur = (*head);
    LINE *temp;

    char ch = getc(file);
    int count = 0;

    while (ch != EOF)
    {
        while ((ch != '\n') && (ch != EOF)) {
            if (count == max_size_line-1) {
                next_line(cur);
                cur = cur->next;
                count = 0;
                (*lines_count)++;
            }
            add_symbol(cur, ch, count, max_size_line);
            count++;

            ch = getc(file);
        }
        ch = getc(file);
        if(ch != EOF)
        {
            next_line(cur);
            cur = cur->next;

            count = 0;
            (*lines_count)++;
        }
    }
	fclose(file);
}