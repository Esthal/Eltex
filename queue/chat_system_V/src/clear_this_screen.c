#include "../client.h"

void clear_this_screen(WINDOW *win, int x, int y)
{
    wmove(win, 0,0);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            wprintw(win, " ");
        }
    }
}