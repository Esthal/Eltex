#include "../client.h"

extern int msg_id;
extern chat *head_online_list;

void get_all_users(char *name)
{
    struct msgbuf message;
    strcpy(message.text, name);
    message.mtype = 8;
    int snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
    if (snd == -1)
    {
        perror("message snd: ");
        msgctl(msg_id, IPC_RMID, NULL);
        exit(-1);
    }

    while (TRUE)
    {
        msgrcv(msg_id, &message, sizeof(struct msgbuf), 11, 0);
        if (strcmp(message.text, "") == 0)
        {
            break;
        }
        
        add_in_list(&head_online_list, message.text);
    }
}