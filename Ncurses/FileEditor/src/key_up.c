#include "../FileEditor.h"

void key_up(LINE **head, LINE **current_line, WINDOW *text_field, int max_size_line, int lines_max, int *cur_line)
{
    int x,y;
    getyx(text_field, y, x);
    
    if((*current_line)->prev != NULL)
    {
        if ((*cur_line) <= 0)
        {
            clear_text(text_field, max_size_line, lines_max);
            (*head) = (*head)->prev;
            print_text((*head), text_field, lines_max);
            y++;
        }
        else
        {
            (*cur_line)--;
        }
        
        (*current_line) = (*current_line)->prev;
        
        if((*current_line)->size > x)
        {
            wmove(text_field, y-1, x);
        }
        else
        {
            wmove(text_field, y-1, (*current_line)->size);
        }
    }
}