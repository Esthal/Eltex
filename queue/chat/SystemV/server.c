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
    int action;
};

typedef struct mes_chat
{
    char mes[MESSSAGE_SIZE];
    struct mes_chat *next;
    struct mes_chat *prev;
} chat;

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

void add_in_list(chat **list,char *mes)
{
    chat *temp = malloc(sizeof(struct mes_chat));
    strcpy(temp->mes , mes);
    temp->next = NULL;
    temp->prev = NULL;

    if ((*list) == NULL)
    {
        (*list) = temp;
    }
    else
    {
        chat *cur = (*list);

        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = temp;
        temp->prev = cur;
    }
}

void delete_user_from_list(chat **list,char *name)
{
    chat *temp = (*list);

    while (temp != NULL)
    {
        if (strcmp(temp->mes, name) == 0)
        {
            if(temp->prev == NULL && temp->next == NULL)
            {
                free(temp);
                (*list) = NULL;
                printf("->1\n");
            }
            else if (temp->prev == NULL)
            {
                (*list) = (*list)->next;
                (*list)->prev = NULL;
                free(temp);
                printf("->2\n");
            }
            else if (temp->next == NULL)
            {
                temp = temp->prev;
                temp->next = NULL;
                free(temp->next);
                printf("->3\n");
            }
            else
            {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
                temp->next == NULL;
                temp->prev == NULL;
                free(temp);
                printf("->4\n");
            }
            break;
            
        }
        temp = temp->next;
    }

}


int main()
{
    chat *user_list = NULL;
    char new_message[MESSSAGE_SIZE];
    int msg_id = connect_to_queue("queue", 8);
    struct msgbuf message;
    int rcv;
    int snd;

    chat *temp;

   

    while (1)
    {
        rcv = msgrcv(msg_id, &message, sizeof(struct msgbuf), -9,0);
        if (rcv == -1)
        {
            perror("message rcv: ");
        }
        
        printf("type %ld \n", message.mtype);

        switch (message.mtype)
        {
        case 1:
            printf("msg from client (%ld): %s\n", message.mtype, message.text);
            temp = user_list;

            message.mtype = 12;
            while (temp != NULL)
            {
                snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
                if (snd == -1)
                {
                    perror("message snd: ");
                    msgctl(msg_id, IPC_RMID, NULL);
                    exit(-1);
                }
                temp = temp->next;
            }
            


            message.mtype = 10;
            snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
            if (snd == -1)
            {
                perror("message snd: ");
                msgctl(msg_id, IPC_RMID, NULL);
                exit(-1);
            }
            break;



        case 8:
            printf("User %s is connect\n", message.text);

            temp = user_list;

            message.mtype = 14;
            message.action = 1;
            while (temp != NULL)
            {
                snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
                if (snd == -1)
                {
                    perror("message snd: ");
                    msgctl(msg_id, IPC_RMID, NULL);
                    exit(-1);
                }
                temp = temp->next;
            }




            add_in_list(&user_list, message.text);
            temp = user_list;
            message.mtype = 11;
            while (temp != NULL)
            {
                strcpy(message.text, temp->mes);
                snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
                if (snd == -1)
                {
                    perror("message snd: ");
                    msgctl(msg_id, IPC_RMID, NULL);
                    exit(-1);
                }
                temp = temp->next;
            }
            strcpy(message.text, "");
            snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
            if (snd == -1)
            {
                perror("message snd: ");
                msgctl(msg_id, IPC_RMID, NULL);
                exit(-1);
            }
            break;

        case 9:
            temp = user_list;
            message.mtype = 15;
            printf("delete %s\n", message.text);
            while (temp != NULL)
            {
                snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
                if (snd == -1)
                {
                    perror("message snd: ");
                    msgctl(msg_id, IPC_RMID, NULL);
                    exit(-1);
                }
                temp = temp->next;
            }

            printf("Delete user %s\n", message.text);
            delete_user_from_list(&user_list,message.text);
            break;
        }

        


    }
    
    return 0;
}