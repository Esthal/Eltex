#include "../client.h"

extern WINDOW *screen_message_list;


char *get_name(void)
{
    char *name = malloc(NAME_SIZE);

    curs_set(TRUE);
    wattron(screen_message_list, A_BOLD);
    wmove(screen_message_list, 0, 0);
    wprintw(screen_message_list, "Enter your name: ");
    wgetnstr(screen_message_list, name, NAME_SIZE);
    curs_set(FALSE);

    get_all_users(name);

    return name;
}