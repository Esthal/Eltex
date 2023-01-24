#include "../FileEditor.h"

void key_right(LINE **current_line, WINDOW *text_field, int max_size)
{
    int x, y;
    getyx(text_field, y, x);
    if(x <= max_size-3)
    {
        if (x < (*current_line)->size)
        {
            wmove(text_field, y, x+1);
        }
        else
        {
            if ((*current_line)->next != NULL)
            {
                wmove(text_field, y+1, 0);
                (*current_line) = (*current_line)->next;
            }
        }
    }
    else
    {
        if ((*current_line)->next != NULL)
        {
            wmove(text_field, y+1, 0);
            (*current_line) = (*current_line)->next;
        }
    }
}