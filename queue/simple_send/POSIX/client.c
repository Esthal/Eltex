#include "queue.h"

int main()
{
    char buffer[MAX_SIZE];    
    int send;
    ssize_t bytes_read;

    mqd_t mq_id = mq_open("/queue", O_CREAT | O_RDWR);
    if(mq_id == -1)
    {
        perror("mq open: ");
        printf("Open server\n");
        exit(-1);
    }
    
    while (1)
    {
        printf("Send to server:");
        memset(buffer, 0, MAX_SIZE);
        fgets(buffer, MAX_SIZE, stdin);

        if(strcmp(buffer, "exit\n") == 0)
        {
            send = mq_send(mq_id, buffer, MAX_SIZE, 5);
            if(send == -1)
            {
                perror("mq send: ");
                exit(-1);
            }
            break;
        }

        send = mq_send(mq_id, buffer, MAX_SIZE, 1);
        if(send == -1)
        {
            perror("mq send: ");
            exit(-1);
        }


        bytes_read = mq_receive(mq_id, buffer, MAX_SIZE, NULL);
        if (bytes_read == -1)
        {
            perror("mq receive: ");
            exit(-1);
        }
        buffer[bytes_read] = '\0';
        printf("Server: %s\n", buffer);
        
    }
    

    mq_close(mq_id);
    return 0;
}