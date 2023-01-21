#include "queue.h"

int main()
{
    char buffer[MAX_SIZE + 1];
    int priority;
    ssize_t bytes_read;
    int send;
    
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;

    mqd_t mq_id = mq_open("/queue", O_CREAT | O_RDWR, 0644, &attr);
    if(mq_id == -1)
    {
        perror("mq open: ");
        exit(-1);
    }

    while (1)
    {
        bytes_read = mq_receive(mq_id, buffer, MAX_SIZE, &priority);
        if (bytes_read == -1)
        {
            perror("mq receive: ");
            exit(-1);
        }
        if (priority == 5)
        {
            break;
        }
        buffer[bytes_read] = '\0';
        printf("Client: %s\n", buffer);


        printf("Send to client:");
        memset(buffer, 0, MAX_SIZE);
        fgets(buffer, MAX_SIZE, stdin);

        send = mq_send(mq_id, buffer, MAX_SIZE, 1);
        if (send == -1)
        {
            perror("mq send: ");
            exit(-1);
        }
    }
    
    mq_close(mq_id);
    mq_unlink("/queue");
    return 0;
}