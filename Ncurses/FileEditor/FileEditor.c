#include "FileEditor.h"

int main(int argc, char *argv[])
{
    WINDOW *text_field;
    WINDOW *command_field;
    LINE *HEAD;
    LINE *current_line;
    LINE *up_line;

    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);

    int max_size_line = size.ws_col-2;
    int lines_max = size.ws_row-5;
    int lines_count = 0;
    

    int ch;
    int x,y;

    int cur_line = 0;

    

    if (argc > 1)
    {
        
        initscr();
        curs_set(TRUE);
        start_color();
        box(stdscr, '|', '-');
        refresh();


        command_field = newwin(3, size.ws_col-2, size.ws_row-4, 1);
        box(command_field, '|', '-');
        wbkgd(command_field, COLOR_BLUE);
        wmove(command_field, 1,1);
        wprintw(command_field, "F1: Save|F9: Exit");
        wrefresh(command_field);


        text_field = newwin(size.ws_row-5, size.ws_col-2, 1, 1);
        wbkgd(text_field, COLOR_BLACK);
        keypad(text_field, TRUE);
        wrefresh(text_field);

        if (file_exists(argv[1]))
        {
            load_file(&HEAD, argv[1], max_size_line, &lines_count);
            print_text(HEAD, text_field, lines_max);
        }
        else
        {
            init_page(&HEAD, argv[1]);
        }

    }
    else
    {
        printf("Enter file\n");
        exit(0);
    }


    current_line = HEAD;
    up_line = HEAD;

    wmove(text_field, 0, 0);
    while (TRUE)
    {
        ch = wgetch(text_field);

        switch (ch)
        {
        case KEY_BACKSPACE:
            key_backspace(current_line, text_field);
            break;

        case KEY_UP:
            key_up(&up_line, &current_line, text_field, max_size_line, lines_max, &cur_line);
            break;

        case KEY_DOWN:
            key_down(&up_line, &current_line, text_field, max_size_line, &lines_count, lines_max, &cur_line);
            break;

        case KEY_LEFT:
            key_left(&current_line, text_field);
            break;

        case KEY_RIGHT:
            key_right(&current_line, text_field, max_size_line);
            break;  

        case KEY_F(1):
            save_file(HEAD, argv[1]);
            break;

        case KEY_F(9):
            delwin(text_field);
            delwin(command_field);
            endwin();
            exit(EXIT_SUCCESS);
            break;
        
        default:
            getyx(text_field, y, x);
            if (max_size_line-1 > x)
            {
                add_symbol(current_line, ch, x-1, max_size_line);
            }
            else
            {
                wmove(text_field, y, x-1);
            }
            
            break;
        }
    }
       

}