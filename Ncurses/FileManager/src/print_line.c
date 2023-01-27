#include "../FileManager.h"

void print_line(WINDOW *window, char *line, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (line[i] == '\0')
        {
            break;
        }
        
        wprintw(window, "%c", line[i]);
    }    
}