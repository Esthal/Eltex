#include "server.h"

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