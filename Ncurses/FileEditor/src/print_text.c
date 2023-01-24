#include "../FileEditor.h"

void print_text(LINE *head, WINDOW *text_field, int max_lines)
{
    LINE *write_lines = head;
    int i = 0;
            
    while (write_lines != NULL)
    {
        if(i < max_lines)
        {
            wmove(text_field, i, 0);
            wprintw(text_field, "%s", write_lines->line);

            write_lines = write_lines->next;
            i++;
        }
        else
        {
            break;
        }
    }
}