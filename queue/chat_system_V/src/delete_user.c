#include "../client.h"

extern int msg_id;
extern char *user_name;

void delete_user(void)
{
    struct msgbuf message;
    strcpy(message.text, user_name);
    message.mtype = 9;
    int snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
    if (snd == -1)
    {
        perror("message snd: ");
        msgctl(msg_id, IPC_RMID, NULL);
        exit(-1);
    }
}