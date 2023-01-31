#include "../client.h"

extern struct winsize size_chat_list;
extern WINDOW *screen_chat_list;
extern WINDOW *screen_message_list;

extern int msg_id;
extern chat *head;

void *chat_thread()
{
    struct msgbuf message;
    
    int rcv;
    
    while (TRUE)
    {
        rcv = msgrcv(msg_id, &message, sizeof(struct msgbuf), 12, 0);
        if (rcv == -1)
        {
            perror("message rcv: ");
        }
        add_in_list(&head, message.text);
        clear_this_screen(screen_chat_list, size_chat_list.ws_col, size_chat_list.ws_row);
        print_list(head, screen_chat_list);
        wrefresh(screen_chat_list);

        wmove(screen_message_list, 0, 0);
        wrefresh(screen_message_list);
        sleep(1);
    }
}