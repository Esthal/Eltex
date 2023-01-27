#include "../FileManager.h"

void print_pwd(WINDOW *window, char *line, int count)
{
    int i;
    int start_line = strlen(line);

    if (start_line > count)
    {
        start_line = start_line-count;
    }
    else
    {
        start_line = 0;
    }

    
    for (i = start_line; i < count+start_line; i++)
    {
        if (line[i] == '\0')
        {
            break;
        }
        
        wprintw(window, "%c", line[i]);
    }    

    while (i < count)
    {
        wprintw(window, "-");
        i++;
    }
     
}