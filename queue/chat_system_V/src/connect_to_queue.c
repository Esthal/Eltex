#include "../client.h"

int connect_to_queue(char *pathname, int proj_id)
{
    int fd = open(pathname, O_CREAT, 0666);
    if (fd == -1)
    {
        perror("file create");
        exit(-1);
    }
    close(fd);
    
    key_t key = ftok(pathname, proj_id);
    if (key == -1)
    {
        perror("fail");
    }

    int msg = msgget(key, IPC_CREAT | 0666);
    if (msg == -1)
    {
        perror("message: ");
        exit(-1);
    }

    return msg;
}