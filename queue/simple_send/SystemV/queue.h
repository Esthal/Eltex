#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <string.h>

#include <errno.h>
#include <unistd.h>

struct msgbuf
{
    long mtype;
    char text[80];
};

int connect_to_queue(char *, int);

#endif