#include "../client.h"

extern WINDOW *screen_message_list;

void get_user_message(char *message)
{
    memset(message, 0, MESSSAGE_SIZE);
    curs_set(TRUE);
    wattron(screen_message_list, A_BOLD);
    wmove(screen_message_list, 0, 0);
    wgetnstr(screen_message_list, message, MESSSAGE_SIZE - NAME_SIZE - 1);
    curs_set(FALSE);
}