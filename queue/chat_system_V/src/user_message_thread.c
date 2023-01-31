#include "../client.h"

extern struct winsize size_message_list;
extern WINDOW *screen_message_list;

extern int msg_id;
extern char *user_name;

void *user_message_thread()
{
    struct msgbuf message;
    char new_msg[MESSSAGE_SIZE];
    
    int snd;

    
    while (TRUE)
    {
        memset(new_msg, 0, MESSSAGE_SIZE);
        get_user_message(message.text);
        if (strcmp(message.text, "") == 0)
        {
            continue;
        }
        strcpy(new_msg, user_name);
        strcat(new_msg, ": ");
        strcat(new_msg, message.text);

        strcpy(message.text, new_msg);


        clear_this_screen(screen_message_list, size_message_list.ws_col, size_message_list.ws_row);
        wrefresh(screen_message_list);
        
        message.mtype = 1;
        snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
        if (snd == -1)
        {
            perror("message snd: ");
            msgctl(msg_id, IPC_RMID, NULL);
            exit(-1);
        }
        wmove(screen_message_list, 0, 0);
    }
}