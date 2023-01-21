#include "queue.h"

int main()
{
    int msg = connect_to_queue("queue", 8);

    struct msgbuf message;
    int snd;
    int rcv;
    while (1)
    {
        rcv = msgrcv(msg, &message, sizeof(struct msgbuf), 0,0);
        if (message.mtype == 5){
            msgctl(msg, IPC_RMID, NULL);
            exit(0);
        }
        if (rcv == -1)
        {
            perror("message rcv: ");
            exit(-1);
        }
        printf("msg from client: %s\n", message.text);

        
        printf("send to client: ");
        scanf("%79s", message.text);
        message.mtype = 1;
        snd = msgsnd(msg, &message, strlen(message.text)+1, 0);
        if (snd == -1)
        {
            perror("message snd: ");
            msgctl(msg, IPC_RMID, NULL);
            exit(-1);
        }
    }
    return 0;
}