#include "FileManager.h"

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
    init_pair(4, COLOR_WHITE, COLOR_BLACK);

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
    whline(command_field, '=', size_command_field.x);

    keypad(dir_field_left, TRUE);
    keypad(dir_field_right, TRUE);

    wmove(command_field, 1, 1);
    wprintw(command_field, "F1: Change screen | F2: Create file | F3: Delete file | F4: Move file");
    wmove(command_field, 2, 1);
    wprintw(command_field, "F5: Copy file | F6: Rename file | Left arrow: Open dir | F9: Quit");


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

    char *name_file;

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
            name_file = get_string(dir_field, size_dir_field);
            create_file(cwd, name_file);
            free(name_file);

            box(dir_field_left, '|', '-');
            box(dir_field_right, '|', '-');

            wrefresh(dir_field_left);
            wrefresh(dir_field_right);

            need_refresh_screens = TRUE;
            break;
        case KEY_F(3):

            if((*cur)->size != -1)
            {
                (*chosen_line)--;
                delete_file(cwd, (*cur)->name);
                (*cur) = (*cur)->prev;
            } 
            
            need_refresh_screens = TRUE;
            break;
        case KEY_F(4):
            if (use_left_field)
            {
                move_file(cwd_left, cwd_right, (*cur)->name);
            }
            else
            {
                move_file(cwd_right, cwd_left, (*cur)->name);
            }
            need_refresh_screens = TRUE;
            break;
        case KEY_F(5):
            copy_file(cwd, (*cur)->name);
            need_refresh_screens = TRUE;
            break;
        case KEY_F(6):
            name_file = get_string(dir_field, size_dir_field);
            rename_file(cwd, (*cur)->name, name_file);
            free(name_file);

            box(dir_field_left, '|', '-');
            box(dir_field_right, '|', '-');

            wrefresh(dir_field_left);
            wrefresh(dir_field_right);

            need_refresh_screens = TRUE;
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