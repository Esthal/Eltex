#include "../FileManager.h"

char *get_string(WINDOW *window, WinSize size)
{
    int size_name = 30;
    int size_x = 32;
    int size_y = 5;


    char *name = malloc(size_name+1);
    WINDOW *enter_name = derwin(window, size_y, size_x + 1,size.y/3, size.x/2 - size_x/2);
    wbkgd(enter_name, COLOR_PAIR(4));
    box(enter_name, '|', '=');

    curs_set(TRUE);
    wattron(enter_name, A_BOLD);
    wmove(enter_name, 1, 1);
    wprintw(enter_name, "Enter file name:");
    wmove(enter_name, 2, 1);
    wgetnstr(enter_name, name, size_name);

    wrefresh(enter_name);
    delwin(enter_name);
    curs_set(FALSE);

    return name;
}