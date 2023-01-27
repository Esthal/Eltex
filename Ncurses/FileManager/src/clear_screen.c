#include "../FileManager.h"

void clear_screen(WINDOW *window, WinSize size)
{
    for(int i=1; i<size.y-1; i++)
    {
        wmove(window, i, 1);
        whline(window, ' ', size.x-2);
    }
}