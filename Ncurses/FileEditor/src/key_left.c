#include "../FileEditor.h"

void key_left(LINE **current_line, WINDOW *text_field)
{
    int x,y;
    getyx(text_field, y, x);
    if (x == 0 && y != 0)
    {
        (*current_line) = (*current_line)->prev;
        wmove(text_field, y-1, (*current_line)->size);      
        
    }
    else
    {
        wmove(text_field, y, x-1);
    }
}