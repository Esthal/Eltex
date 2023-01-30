#include "client.h"


struct winsize size;
struct winsize size_chat;
struct winsize size_chat_list;
struct winsize size_message;
struct winsize size_message_list;
struct winsize size_users_online;
struct winsize size_users_online_list;

WINDOW *screen_chat;
WINDOW *screen_chat_list;
WINDOW *screen_message;
WINDOW *screen_message_list;
WINDOW *screen_users_online;
WINDOW *screen_users_online_list;

pthread_t user_index;
pthread_t chat_index;
pthread_t online_index;
pthread_t offline_index;

int msg_id;
char *user_name;

chat *head;
chat *head_online_list;

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

void set_size_screen(void)
{
    size_chat.ws_col = size.ws_col/4 * 3;
    size_chat.ws_row = size.ws_row/3 * 2;
    size_chat.ws_xpixel = 1;
    size_chat.ws_ypixel = 1;

    size_chat_list.ws_col = size_chat.ws_col - 2;
    size_chat_list.ws_row = size_chat.ws_row - 2;
    size_chat_list.ws_xpixel = 1;
    size_chat_list.ws_ypixel = 1;
    

    size_message.ws_col = size.ws_col/4 * 3;
    size_message.ws_row = size.ws_row/3 + size.ws_row%3 - 2;
    size_message.ws_xpixel = 1;
    size_message.ws_ypixel = size.ws_row/3 * 2 + 1;

    size_message_list.ws_col = size_message.ws_col - 2;
    size_message_list.ws_row = size_message.ws_row - 2;
    size_message_list.ws_xpixel = 1;
    size_message_list.ws_ypixel = 1;

    size_users_online.ws_col = size.ws_col/4 + size.ws_col%4 - 2;
    size_users_online.ws_row = size.ws_row - 2;
    size_users_online.ws_xpixel = size.ws_col/4 * 3 + 1;
    size_users_online.ws_ypixel = 1;

    size_users_online_list.ws_col = size_users_online.ws_col - 2;
    size_users_online_list.ws_row = size_users_online.ws_row - 2;
    size_users_online_list.ws_xpixel = 1;
    size_users_online_list.ws_ypixel = 1;
}

void clear_this_screen(WINDOW *win, int x, int y)
{
    wmove(win, 0,0);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            wprintw(win, " ");
        }
    }
}


void clear_screen(void)
{
    clear_this_screen(stdscr, size.ws_col, size.ws_row);

    clear_this_screen(screen_chat, size_chat.ws_col, size_chat.ws_row);
    clear_this_screen(screen_chat_list, size_chat_list.ws_col, size_chat_list.ws_row);

    clear_this_screen(screen_message, size_message.ws_col, size_message.ws_row);
    clear_this_screen(screen_message_list, size_message_list.ws_col, size_message_list.ws_row);

    clear_this_screen(screen_users_online, size_users_online.ws_col, size_users_online.ws_row);
    clear_this_screen(screen_users_online_list, size_users_online_list.ws_col, size_users_online_list.ws_row);

}


void resize_all(void)
{
    clear_screen();

    wresize(screen_chat, size_chat.ws_row, size_chat.ws_col);
    wresize(screen_chat_list, size_chat_list.ws_row, size_chat_list.ws_col);

    mvwin(screen_message, size_message.ws_ypixel, size_message.ws_xpixel);
    wresize(screen_message, size_message.ws_row, size_message.ws_col);

    wresize(screen_message_list, size_message_list.ws_row, size_message_list.ws_col);
    
    mvwin(screen_users_online, size_users_online.ws_ypixel, size_users_online.ws_xpixel);
    wresize(screen_users_online, size_users_online.ws_row, size_users_online.ws_col);

    wresize(screen_users_online_list, size_users_online_list.ws_row, size_users_online_list.ws_col);
    
    box(stdscr, '|', '=');
    box(screen_chat, '|', '=');
    box(screen_message, '|', '=');
    box(screen_users_online, '|', '=');
    print_list(head, screen_chat_list);
    print_list(head_online_list, screen_users_online_list);
    refresh();
    wrefresh(screen_chat);
    wrefresh(screen_chat_list);
    wrefresh(screen_message);
    wrefresh(screen_message_list);
    wrefresh(screen_users_online);
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

void sig_winch()
{
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    set_size_screen();
    resize_all();
}

void delete_user(void)
{
    struct msgbuf message;
    strcpy(message.text, user_name);
    message.mtype = 9;
    int snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
    if (snd == -1)
    {
        perror("message snd: ");
        msgctl(msg_id, IPC_RMID, NULL);
        exit(-1);
    }
}

void quit(void)
{
    delete_user();
    free(user_name);

    pthread_cancel(user_index);
    pthread_cancel(chat_index);
    pthread_cancel(online_index);
    pthread_cancel(offline_index);
    delwin(screen_chat);
    delwin(screen_chat_list);
    delwin(screen_message);
    delwin(screen_message_list);
    delwin(screen_users_online);
    delwin(screen_users_online_list);
    endwin();
    exit(EXIT_SUCCESS);
}

void init_main_window(void)
{
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);

    set_size_screen();

    initscr();
    signal(SIGWINCH, (void *) sig_winch);
    signal(SIGINT, (void *) quit);
    curs_set(FALSE);
    cbreak();
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    bkgd(COLOR_PAIR(1));

    screen_chat = newwin(
        size_chat.ws_row, 
        size_chat.ws_col, 
        size_chat.ws_ypixel, 
        size_chat.ws_xpixel);
    
    screen_chat_list = derwin(
        screen_chat, 
        size_chat_list.ws_row, 
        size_chat_list.ws_col, 
        size_chat_list.ws_ypixel, 
        size_chat_list.ws_xpixel);
    
    screen_message = newwin(
        size_message.ws_row, 
        size_message.ws_col, 
        size_message.ws_ypixel, 
        size_message.ws_xpixel);

    screen_message_list = derwin(
        screen_message,
        size_message_list.ws_row, 
        size_message_list.ws_col, 
        size_message_list.ws_ypixel, 
        size_message_list.ws_xpixel);
    
    screen_users_online = newwin(
        size_users_online.ws_row, 
        size_users_online.ws_col, 
        size_users_online.ws_ypixel, 
        size_users_online.ws_xpixel);
    
    screen_users_online_list = derwin(
        screen_users_online, 
        size_users_online_list.ws_row, 
        size_users_online_list.ws_col, 
        size_users_online_list.ws_ypixel, 
        size_users_online_list.ws_xpixel);
    
    resize_all();
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



void print_list(chat *list, WINDOW *win)
{
    int line = 1;
    wmove(win, 0, 0);
    while (list != NULL)
    {
        wprintw(win, "%s\n", list->mes);
        list = list->next;
    }
    wrefresh(win);
    
}

void get_user_message(char *message)
{
    memset(message, 0, MESSSAGE_SIZE);

    curs_set(TRUE);
    wattron(screen_message_list, A_BOLD);
    wmove(screen_message_list, 0, 0);
    wgetnstr(screen_message_list, message, MESSSAGE_SIZE - NAME_SIZE - 1);
    curs_set(FALSE);
}

char *get_name(void)
{
    char *name = malloc(NAME_SIZE);

    curs_set(TRUE);
    wattron(screen_message_list, A_BOLD);
    wmove(screen_message_list, 0, 0);
    wprintw(screen_message_list, "Enter your name: ");
    wgetnstr(screen_message_list, name, NAME_SIZE);
    curs_set(FALSE);


    
    get_all_users(name);

    return name;
}

void get_all_users(char *name)
{
    struct msgbuf message;
    strcpy(message.text, name);
    message.mtype = 8;
    int snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
    if (snd == -1)
    {
        perror("message snd: ");
        msgctl(msg_id, IPC_RMID, NULL);
        exit(-1);
    }

    while (TRUE)
    {
        msgrcv(msg_id, &message, sizeof(struct msgbuf), 11, 0);
        if (strcmp(message.text, "") == 0)
        {
            break;
        }
        
        add_in_list(&head_online_list, message.text);
    }
}

void get_all_chat(void)
{
    struct msgbuf message;
    struct msqid_ds buf;
    int rcv;

    msgctl(msg_id, IPC_STAT, &buf);

    for (int i = 0; i < buf.msg_qnum; i++)
    {
        rcv = msgrcv(msg_id, &message, sizeof(struct msgbuf), 10, 0);
        add_in_list(&head, message.text);
    }
    
    chat *temp = head;

    message.mtype = 10;
    while (temp != NULL)
    {
        strcpy(message.text, temp->mes);
        msgsnd(msg_id, &message, strlen(message.text)+1, 0);
        temp=temp->next;
    }
    
    
}

void *user_message_thread()
{
    struct msgbuf message;
    char new_msg[MESSSAGE_SIZE];
    
    int snd;

    
    while (TRUE)
    {
        memset(new_msg, 0, MESSSAGE_SIZE);
        get_user_message(message.text);
        if (strcmp(message.text, "") == 0)
        {
            continue;
        }
        strcpy(new_msg, user_name);
        strcat(new_msg, ": ");
        strcat(new_msg, message.text);

        strcpy(message.text, new_msg);


        clear_this_screen(screen_message_list, size_message_list.ws_col, size_message_list.ws_row);
        wrefresh(screen_message_list);
        
        message.mtype = 1;
        snd = msgsnd(msg_id, &message, strlen(message.text)+1, 0);
        if (snd == -1)
        {
            perror("message snd: ");
            msgctl(msg_id, IPC_RMID, NULL);
            exit(-1);
        }
        wmove(screen_message_list, 0, 0);
    }
}

void *chat_thread()
{
    struct msgbuf message;
    
    int rcv;
    
    while (TRUE)
    {
        rcv = msgrcv(msg_id, &message, sizeof(struct msgbuf), 12, 0);
        if (rcv == -1)
        {
            perror("message rcv: ");
        }
        add_in_list(&head, message.text);
        clear_this_screen(screen_chat_list, size_chat_list.ws_col, size_chat_list.ws_row);
        print_list(head, screen_chat_list);
        wrefresh(screen_chat_list);

        wmove(screen_message_list, 0, 0);
        wrefresh(screen_message_list);
        sleep(1);
    }
}

void *online_thread()
{
    struct msgbuf message;
    
    int rcv;
    
    while (TRUE)
    {
        rcv = msgrcv(msg_id, &message, sizeof(struct msgbuf), 14, 0);
        if (rcv == -1)
        {
            perror("message rcv: ");
        }
        add_in_list(&head_online_list, message.text);
        
        clear_this_screen(screen_users_online_list, size_users_online_list.ws_col, size_users_online_list.ws_row);
        print_list(head_online_list, screen_users_online_list);
        wrefresh(screen_users_online_list);

        wmove(screen_message_list, 0, 0);
        wrefresh(screen_message_list);
        sleep(1);
    }
}

void *offline_thread()
{
    struct msgbuf message;
    
    int rcv;
    
    while (TRUE)
    {
        rcv = msgrcv(msg_id, &message, sizeof(struct msgbuf), 15, 0);
        if (rcv == -1)
        {
            perror("message rcv: ");
        }
        delete_user_from_list(&head_online_list,message.text);
        
        clear_this_screen(screen_users_online_list, size_users_online_list.ws_col, size_users_online_list.ws_row);
        print_list(head_online_list, screen_users_online_list);
        wrefresh(screen_users_online_list);

        wmove(screen_message_list, 0, 0);
        wrefresh(screen_message_list);
        sleep(1);
    }
}

int main()
{
    head = NULL;
    head_online_list = NULL;

    msg_id = connect_to_queue("queue", 8);

    
    init_main_window();
    
    
    user_name = get_name();
    get_all_chat();


    

    clear_this_screen(screen_message_list, size_message_list.ws_col, size_message_list.ws_row);


    print_list(head, screen_chat_list);
    print_list(head_online_list, screen_users_online_list);

    

    int s = pthread_create(&user_index, NULL, user_message_thread, NULL);
    if (s != 0)
    {
        perror("error: create\n");
    }
    s = pthread_create(&chat_index, NULL, chat_thread, NULL);
    if (s != 0)
    {
        perror("error: create\n");
    }
    s = pthread_create(&online_index, NULL, online_thread, NULL);
    if (s != 0)
    {
        perror("error: create\n");
    }
    s = pthread_create(&offline_index, NULL, offline_thread, NULL);
    if (s != 0)
    {
        perror("error: create\n");
    }

    s = pthread_join(user_index, NULL);
    if (s != 0)
    {
        perror("error: join\n");
    }

    s = pthread_join(chat_index, NULL);
    if (s != 0)
    {
        perror("error: join\n");
    }
    s = pthread_join(online_index, NULL);
    if (s != 0)
    {
        perror("error: join\n");
    }
    s = pthread_join(offline_index, NULL);
    if (s != 0)
    {
        perror("error: join\n");
    }

    
    exit(EXIT_SUCCESS);
}