#include "../client.h"

extern struct winsize size;
extern struct winsize size_chat;
extern struct winsize size_chat_list;
extern struct winsize size_message;
extern struct winsize size_message_list;
extern struct winsize size_users_online;
extern struct winsize size_users_online_list;

void set_size_screen(void)
{
    size_chat.ws_col = size.ws_col/4 * 3;
    size_chat.ws_row = size.ws_row/3 * 2;
    size_chat.ws_xpixel = 1;
    size_chat.ws_ypixel = 1;

    size_chat_list.ws_col = size_chat.ws_col - 2;
    size_chat_list.ws_row = size_chat.ws_row - 2;
    size_chat_list.ws_xpixel = 1;
    size_chat_list.ws_ypixel = 1;
    

    size_message.ws_col = size.ws_col/4 * 3;
    size_message.ws_row = size.ws_row/3 + size.ws_row%3 - 2;
    size_message.ws_xpixel = 1;
    size_message.ws_ypixel = size.ws_row/3 * 2 + 1;

    size_message_list.ws_col = size_message.ws_col - 2;
    size_message_list.ws_row = size_message.ws_row - 2;
    size_message_list.ws_xpixel = 1;
    size_message_list.ws_ypixel = 1;

    size_users_online.ws_col = size.ws_col/4 + size.ws_col%4 - 2;
    size_users_online.ws_row = size.ws_row - 2;
    size_users_online.ws_xpixel = size.ws_col/4 * 3 + 1;
    size_users_online.ws_ypixel = 1;

    size_users_online_list.ws_col = size_users_online.ws_col - 2;
    size_users_online_list.ws_row = size_users_online.ws_row - 2;
    size_users_online_list.ws_xpixel = 1;
    size_users_online_list.ws_ypixel = 1;
}