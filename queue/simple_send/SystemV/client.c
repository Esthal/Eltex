#include "queue.h"

int main()
{
    int msg = connect_to_queue("queue", 8);

    struct msgbuf message;
    int snd;
    int rcv;
    while (1)
    {
        printf("send to server: ");
        scanf("%79s", message.text);

        if (strcmp(message.text,"exit") == 0)
        {
            message.mtype = 5;
            snd = msgsnd(msg, &message, 0, 0);
            if (snd == -1)
            {
                msgctl(msg, IPC_RMID, NULL);
                exit(-1);
            }
            break;
        }

        message.mtype = 1;
        snd = msgsnd(msg, &message, strlen(message.text)+1, 0);
        if (snd == -1)
        {
            perror("message snd: ");
            msgctl(msg, IPC_RMID, NULL);
            exit(-1);
        }


        rcv = msgrcv(msg, &message, sizeof(struct msgbuf), 0,0);
        if (rcv == -1)
        {
            perror("message rcv: ");
        }
        printf("msg from server: %s\n", message.text);
    }
    return 0;
}