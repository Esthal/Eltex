#ifndef CLIENT_H
#define CLIENT_H

#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <string.h>

#include <errno.h>
#include <unistd.h>

#include <pthread.h>

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

void set_size_screen(void);
void clear_this_screen(WINDOW *, int, int);
void clear_screen(void);
void resize_all(void);
void delete_user_from_list(chat **,char *);
void sig_winch(void);
void delete_user(void);
void quit(void);
void init_main_window(void);
int connect_to_queue(char *, int);
void add_in_list(chat **,char *);
void print_list(chat *, WINDOW *);
void get_user_message(char *);
char *get_name(void);
void get_all_users(char *);
void get_all_chat(void);
void *user_message_thread();
void *chat_thread();
void *online_thread();
void *offline_thread();

#endif