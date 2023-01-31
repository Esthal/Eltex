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
extern WINDOW *stdscr;

extern chat *head;
extern chat *head_online_list;

void resize_all(void)
{
    clear_screen();

    wresize(screen_chat, size_chat.ws_row, size_chat.ws_col);
    wresize(screen_chat_list, size_chat_list.ws_row, size_chat_list.ws_col);

    mvwin(screen_message, size_message.ws_ypixel, size_message.ws_xpixel);
    wresize(screen_message, size_message.ws_row, size_message.ws_col);

    wresize(screen_message_list, size_message_list.ws_row, size_message_list.ws_col);
    
    mvwin(screen_users_online, size_users_online.ws_ypixel, size_users_online.ws_xpixel);
    wresize(screen_users_online, size_users_online.ws_row, size_users_online.ws_col);

    wresize(screen_users_online_list, size_users_online_list.ws_row, size_users_online_list.ws_col);
    
    box(stdscr, '|', '=');
    box(screen_chat, '|', '=');
    box(screen_message, '|', '=');
    box(screen_users_online, '|', '=');
    print_list(head, screen_chat_list);
    print_list(head_online_list, screen_users_online_list);
    refresh();
    wrefresh(screen_chat);
    wrefresh(screen_chat_list);
    wrefresh(screen_message);
    wrefresh(screen_message_list);
    wrefresh(screen_users_online);
}