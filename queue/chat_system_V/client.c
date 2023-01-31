#include "client.h"


struct winsize size;
struct winsize size_chat;
struct winsize size_chat_list;
struct winsize size_message;
struct winsize size_message_list;
struct winsize size_users_online;
struct winsize size_users_online_list;

WINDOW *screen_chat;
WINDOW *screen_chat_list;
WINDOW *screen_message;
WINDOW *screen_message_list;
WINDOW *screen_users_online;
WINDOW *screen_users_online_list;

pthread_t user_index;
pthread_t chat_index;
pthread_t online_index;
pthread_t offline_index;

int msg_id;
char *user_name;

chat *head;
chat *head_online_list;



int main()
{
    head = NULL;
    head_online_list = NULL;

    msg_id = connect_to_queue("queue", 8);

    
    init_main_window();
    
    
    user_name = get_name();
    get_all_chat();


    

    clear_this_screen(screen_message_list, size_message_list.ws_col, size_message_list.ws_row);


    print_list(head, screen_chat_list);
    print_list(head_online_list, screen_users_online_list);

    

    int s = pthread_create(&user_index, NULL, user_message_thread, NULL);
    if (s != 0)
    {
        perror("error: create\n");
    }
    s = pthread_create(&chat_index, NULL, chat_thread, NULL);
    if (s != 0)
    {
        perror("error: create\n");
    }
    s = pthread_create(&online_index, NULL, online_thread, NULL);
    if (s != 0)
    {
        perror("error: create\n");
    }
    s = pthread_create(&offline_index, NULL, offline_thread, NULL);
    if (s != 0)
    {
        perror("error: create\n");
    }

    s = pthread_join(user_index, NULL);
    if (s != 0)
    {
        perror("error: join\n");
    }

    s = pthread_join(chat_index, NULL);
    if (s != 0)
    {
        perror("error: join\n");
    }
    s = pthread_join(online_index, NULL);
    if (s != 0)
    {
        perror("error: join\n");
    }
    s = pthread_join(offline_index, NULL);
    if (s != 0)
    {
        perror("error: join\n");
    }

    
    exit(EXIT_SUCCESS);
}