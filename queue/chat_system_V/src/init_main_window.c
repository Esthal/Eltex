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

void init_main_window(void)
{
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);

    set_size_screen();

    initscr();
    signal(SIGWINCH, (void *) sig_winch);
    signal(SIGINT, (void *) quit);
    curs_set(FALSE);
    cbreak();
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    bkgd(COLOR_PAIR(1));

    screen_chat = newwin(
        size_chat.ws_row, 
        size_chat.ws_col, 
        size_chat.ws_ypixel, 
        size_chat.ws_xpixel);
    
    screen_chat_list = derwin(
        screen_chat, 
        size_chat_list.ws_row, 
        size_chat_list.ws_col, 
        size_chat_list.ws_ypixel, 
        size_chat_list.ws_xpixel);
    
    screen_message = newwin(
        size_message.ws_row, 
        size_message.ws_col, 
        size_message.ws_ypixel, 
        size_message.ws_xpixel);

    screen_message_list = derwin(
        screen_message,
        size_message_list.ws_row, 
        size_message_list.ws_col, 
        size_message_list.ws_ypixel, 
        size_message_list.ws_xpixel);
    
    screen_users_online = newwin(
        size_users_online.ws_row, 
        size_users_online.ws_col, 
        size_users_online.ws_ypixel, 
        size_users_online.ws_xpixel);
    
    screen_users_online_list = derwin(
        screen_users_online, 
        size_users_online_list.ws_row, 
        size_users_online_list.ws_col, 
        size_users_online_list.ws_ypixel, 
        size_users_online_list.ws_xpixel);
    
    resize_all();
}