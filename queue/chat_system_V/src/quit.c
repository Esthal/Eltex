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

extern pthread_t user_index;
extern pthread_t chat_index;
extern pthread_t online_index;
extern pthread_t offline_index;

extern int msg_id;
extern char *user_name;

extern chat *head;
extern chat *head_online_list;

void quit(void)
{
    delete_user();
    free(user_name);

    pthread_cancel(user_index);
    pthread_cancel(chat_index);
    pthread_cancel(online_index);
    pthread_cancel(offline_index);
    delwin(screen_chat);
    delwin(screen_chat_list);
    delwin(screen_message);
    delwin(screen_message_list);
    delwin(screen_users_online);
    delwin(screen_users_online_list);
    endwin();
    exit(EXIT_SUCCESS);
}