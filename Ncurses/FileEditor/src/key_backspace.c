#include "../FileEditor.h"

void key_backspace(LINE *current_line, WINDOW *text_field)
{
    int x,y;
    getyx(text_field, y, x);
    mvwaddch(text_field, y, x, ' ');
    add_symbol(current_line, ' ', x, 0);
    wmove(text_field, y, x);
}