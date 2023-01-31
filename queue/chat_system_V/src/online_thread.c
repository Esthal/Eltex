#include "../client.h"

extern struct winsize size_users_online_list;

extern WINDOW *screen_message_list;
extern WINDOW *screen_users_online_list;

extern int msg_id;
extern chat *head_online_list;


void *online_thread()
{
    struct msgbuf message;
    
    int rcv;
    
    while (TRUE)
    {
        rcv = msgrcv(msg_id, &message, sizeof(struct msgbuf), 14, 0);
        if (rcv == -1)
        {
            perror("message rcv: ");
        }
        add_in_list(&head_online_list, message.text);
        
        clear_this_screen(screen_users_online_list, size_users_online_list.ws_col, size_users_online_list.ws_row);
        print_list(head_online_list, screen_users_online_list);
        wrefresh(screen_users_online_list);

        wmove(screen_message_list, 0, 0);
        wrefresh(screen_message_list);
        sleep(1);
    }
}