#include "FileManager.h"

void refresh_list(ManagerDir **list, char *cwd)
{
    clean_dir(list);
    read_dir(cwd, list);
}

void create_file(char *cwd, char *name)
{
    char path[PATH_MAX];
    strcpy(path, ".");
    strcat(path, cwd);
    strcat(path, "/");
    strcat(path, name);

    FILE *fp;
    fp  = fopen(path, "w");
    fclose(fp);
}
void delete_file(char *cwd, char *name)
{
    char path[PATH_MAX];
    strcpy(path, ".");
    strcat(path, cwd);
    strcat(path, "/");
    strcat(path, name);
    remove(path);
}
void move_file(char *cwd_out, char *cwd_in, char *name)
{
    
}
void copy_file(char *cwd, char *name)
{
    char old_path[PATH_MAX];
    char new_path[PATH_MAX];

    strcpy(old_path, ".");
    strcat(old_path, cwd);
    strcat(old_path, "/");
    strcat(old_path, name);

    strcpy(new_path, old_path);
    strcat(new_path, "-copy");

    int pid = fork();
    int status;

    if(pid == 0)
    {
        if (execlp("cp", "cp", old_path, new_path, NULL) == -1)
        {
            exit(EXIT_FAILURE);
        }
    }
    
    do 
    {
        waitpid(pid, &status, WUNTRACED);
    } 
    while (!WIFEXITED(status) && !WIFSIGNALED(status));

    move(0,0);
    printw("%s", old_path);
    move(0,30);
    printw("%s", new_path);
    refresh();
    
}
void rename_file(char *cwd, char *old_name, char *new_name)
{
    
}

int main()
{
    
    ManagerDir *list_left_head = NULL;
    ManagerDir *list_right_head = NULL;

    char cwd_left[PATH_MAX];
    char cwd_right[PATH_MAX];

    set_cwd(cwd_left);
    set_cwd(cwd_right);

    read_dir(cwd_left, &list_left_head);
    read_dir(cwd_right, &list_right_head);

    chdir("/");


    

    WINDOW *dir_field;
    WINDOW *dir_field_left;
    WINDOW *dir_field_right;
    WINDOW *command_field;

    WinSize size_dir_field;
    WinSize size_dir_field_left;
    WinSize size_dir_field_right;
    WinSize size_command_field;


    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    

    initscr();
    curs_set(FALSE);
    start_color();
    

    init_pair(1, COLOR_WHITE, init_color(0,0,0,700));
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);

    bkgd(COLOR_PAIR(1));
    refresh();

    

    int wigth_sub_win = size.ws_col/2;

    set_window_size(&size_dir_field, 0, 0, size.ws_col, size.ws_row-2);
    set_window_size(&size_dir_field_left, 1, 1, wigth_sub_win-1, size_dir_field.y-2);
    set_window_size(&size_dir_field_right, wigth_sub_win, 1, wigth_sub_win-1+(size.ws_col%2), size_dir_field.y-2);
    set_window_size(&size_command_field, 0, size.ws_row-3, size.ws_col, 3);


    
    

    dir_field = newwin(
        size_dir_field.y,
        size_dir_field.x,
        size_dir_field.padding_y,
        size_dir_field.padding_x
    );
    dir_field_left = derwin(
        dir_field, 
        size_dir_field_left.y,
        size_dir_field_left.x,
        size_dir_field_left.padding_y,
        size_dir_field_left.padding_x
    );
    dir_field_right = derwin(
        dir_field, 
        size_dir_field_right.y,
        size_dir_field_right.x,
        size_dir_field_right.padding_y,
        size_dir_field_right.padding_x
    );
    command_field = newwin(
        size_command_field.y,
        size_command_field.x,
        size_command_field.padding_y,
        size_command_field.padding_x
    );


    box(dir_field, '|', '-');
    box(dir_field_left, '|', '-');
    box(dir_field_right, '|', '-');
    box(command_field, '|', '=');

    keypad(dir_field_left, TRUE);
    keypad(dir_field_right, TRUE);

    wmove(command_field, 1, 1);
    wprintw(command_field, "F1: Change screen | F9: Quit");

    wrefresh(dir_field);
    wrefresh(dir_field_left);
    wrefresh(dir_field_right);
    wrefresh(command_field);


    int ch;
    int chosen_line_left = 1;
    int chosen_line_right = 1;
    int *chosen_line;
    int use_left_field = TRUE;

    int need_refresh_screens = FALSE;

    char *cwd;

    WINDOW *using_screen;

    ManagerDir *cur_left = list_left_head;
    ManagerDir *cur_right = list_right_head;
    ManagerDir **cur;

    ManagerDir **this_list;

    WinSize *cur_size;

    while (TRUE)
    {
        if (use_left_field)
        {
            using_screen = dir_field_left;
            cur = &cur_left;
            chosen_line = &chosen_line_left;
            this_list = &list_left_head;
            cwd = cwd_left;
            cur_size = &size_dir_field_left;
        }
        else
        {
            using_screen = dir_field_right;
            cur = &cur_right;
            chosen_line = &chosen_line_right;
            this_list = &list_right_head;
            cwd = cwd_right;
            cur_size = &size_dir_field_right;

        }

        wmove(using_screen, 0,1);
        print_pwd(using_screen, cwd, cur_size->x-2);
        clear_screen(using_screen, *cur_size);
        print_dir(*this_list, using_screen, cur_size, *chosen_line);


        ch = wgetch(using_screen);
        switch (ch)
        {
        case KEY_LEFT:
            if((*cur)->size == -1)
            {
                (*chosen_line)=1;
                goto_dir(this_list, *cur, cwd);
                (*cur) = (*this_list);
            }            
            
            break;


        case KEY_UP:
        
            if ((*cur)->prev != NULL)
            {
                (*chosen_line)--;
                (*cur) = (*cur)->prev;
                if((*chosen_line) == 0)
                {
                    (*chosen_line)++;
                    (*this_list) = (*this_list)->prev;
                }
                
            }

            break;

        case KEY_DOWN:
            if ((*cur)->next != NULL)
            {
                (*chosen_line)++;
                (*cur) = (*cur)->next;
                if((*chosen_line) > cur_size->y-2)
                {
                    (*chosen_line)--;
                    (*this_list) = (*this_list)->next;
                }
            }           

            break;
 

        case KEY_F(1):
            use_left_field = !use_left_field;
            break;
        case KEY_F(2):
            create_file(cwd, "hello.txt");
            need_refresh_screens = TRUE;
            break;
        case KEY_F(3):
            delete_file(cwd, "hello.txt");
            need_refresh_screens = TRUE;
            break;
        case KEY_F(4): // move file
            break;
        case KEY_F(5): // copy file
            copy_file(cwd, "hello.txt");
            need_refresh_screens = TRUE;
            break;
        case KEY_F(6): // rename file
            break;


        case KEY_F(9):
            delwin(dir_field);
            delwin(dir_field_left);
            delwin(dir_field_right);
            delwin(command_field);
            endwin();
            exit(EXIT_SUCCESS);
            break;
        }


        if (need_refresh_screens)
        {
            need_refresh_screens = FALSE;

            refresh_list(this_list, cwd);
            (*cur) = (*this_list);
            (*chosen_line)=1;
            if (use_left_field)
            {
                using_screen = dir_field_right;
                cur = &cur_right;
                chosen_line = &chosen_line_right;
                this_list = &list_right_head;
                cwd = cwd_right;
                cur_size = &size_dir_field_right;
                refresh_list(this_list, cwd);
                (*cur) = (*this_list);
                (*chosen_line)=1; 
                clear_screen(using_screen, *cur_size);
                print_dir(*this_list, using_screen, cur_size, *chosen_line);
                wrefresh(using_screen);


                using_screen = dir_field_left;
                cur = &cur_left;
                chosen_line = &chosen_line_left;
                this_list = &list_left_head;
                cwd = cwd_left;
                cur_size = &size_dir_field_left;
            }
            else
            {
                using_screen = dir_field_left;
                cur = &cur_left;
                chosen_line = &chosen_line_left;
                this_list = &list_left_head;
                cwd = cwd_left;
                cur_size = &size_dir_field_left;
                refresh_list(this_list, cwd);
                (*cur) = (*this_list);
                (*chosen_line)=1; 
                clear_screen(using_screen, *cur_size);
                print_dir(*this_list, using_screen, cur_size, *chosen_line);
                wrefresh(using_screen);


                using_screen = dir_field_right;
                cur = &cur_right;
                chosen_line = &chosen_line_right;
                this_list = &list_right_head;
                cwd = cwd_right;
                cur_size = &size_dir_field_right;
            }
        }
        
    }
    return 0;
}