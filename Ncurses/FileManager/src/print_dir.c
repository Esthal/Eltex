#include "../FileManager.h"

void print_dir(ManagerDir *list, WINDOW *window, WinSize *size, int chosen_line)
{
    int line = 1;
    while (list != NULL)
    {
        if (line == size->y-1)
        {
            break;
        }
        
        wmove(window, line, 1);
        if (chosen_line != line)
        {
            if (list->size == -1)
            {
                wattron(window, COLOR_PAIR(3));
                print_line(window, list->name, size->x-2);
                wattron(window, COLOR_PAIR(1));
            }
            else
            {
                print_line(window, list->name, size->x-2);
            }
            
            
        }
        else
        {
            wattron(window, COLOR_PAIR(2));
            if (list->size == -1)
            {
                print_line(window, list->name, size->x-2);
            }
            else
            {
                print_line(window, list->name, size->x-2);
            }
            wattron(window, COLOR_PAIR(1));
            
        }
        
        
        list = list->next;
        line++;
    }
}