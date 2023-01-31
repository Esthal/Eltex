#include "../client.h"

extern int msg_id;
extern chat *head;

void get_all_chat(void)
{
    struct msgbuf message;
    struct msqid_ds buf;
    int rcv;

    msgctl(msg_id, IPC_STAT, &buf);

    for (int i = 0; i < buf.msg_qnum; i++)
    {
        rcv = msgrcv(msg_id, &message, sizeof(struct msgbuf), 10, 0);
        add_in_list(&head, message.text);
    }
    
    chat *temp = head;

    message.mtype = 10;
    while (temp != NULL)
    {
        strcpy(message.text, temp->mes);
        msgsnd(msg_id, &message, strlen(message.text)+1, 0);
        temp=temp->next;
    }
}