#include "../client.h"

extern struct winsize size;
extern struct winsize size_chat;
extern struct winsize size_chat_list;
extern struct winsize size_message;
extern struct winsize size_message_list;
extern struct winsize size_users_online;
extern struct winsize size_users_online_list;

extern WINDOW *screen_chat;
extern WINDOW *screen_chat_list;
extern WINDOW *screen_message;
extern WINDOW *screen_message_list;
extern WINDOW *screen_users_online;
extern WINDOW *screen_users_online_list;

void clear_screen(void)
{
    clear_this_screen(stdscr, size.ws_col, size.ws_row);

    clear_this_screen(screen_chat, size_chat.ws_col, size_chat.ws_row);
    clear_this_screen(screen_chat_list, size_chat_list.ws_col, size_chat_list.ws_row);

    clear_this_screen(screen_message, size_message.ws_col, size_message.ws_row);
    clear_this_screen(screen_message_list, size_message_list.ws_col, size_message_list.ws_row);

    clear_this_screen(screen_users_online, size_users_online.ws_col, size_users_online.ws_row);
    clear_this_screen(screen_users_online_list, size_users_online_list.ws_col, size_users_online_list.ws_row);

}