#include "../client.h"

void print_list(chat *list, WINDOW *win)
{
    int line = 1;
    wmove(win, 0, 0);
    while (list != NULL)
    {
        wprintw(win, "%s\n", list->mes);
        list = list->next;
    }
    wrefresh(win);
    
}