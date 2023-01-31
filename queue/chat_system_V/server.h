#ifndef SERVER_H
#define SERVER_H

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

#define MESSSAGE_SIZE 255
#define NAME_SIZE 30

struct msgbuf
{
    long mtype;
    char text[MESSSAGE_SIZE];
};

typedef struct mes_chat
{
    char mes[MESSSAGE_SIZE];
    struct mes_chat *next;
    struct mes_chat *prev;
} chat;

int connect_to_queue(char *, int);
void add_in_list(chat **,char *);
void delete_user_from_list(chat **,char *);

#endif