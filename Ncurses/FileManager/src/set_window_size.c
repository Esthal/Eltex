#include "../FileManager.h"

void set_window_size(WinSize *size, int padding_x, int padding_y, int x, int y)
{
    size->padding_x = padding_x;
    size->padding_y = padding_y;
    size->x = x;
    size->y = y;
}