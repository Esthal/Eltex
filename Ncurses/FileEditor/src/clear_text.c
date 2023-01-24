#include "../FileEditor.h"

void clear_text(WINDOW *text_field, int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            wmove(text_field,i,j);
            mvwaddch(text_field, i, j, ' ');
        }
        
    }
}