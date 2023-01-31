#include "../client.h"

extern struct winsize size;

void sig_winch()
{
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    set_size_screen();
    resize_all();
}