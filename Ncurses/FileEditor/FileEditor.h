#ifndef FILE_EDITOR_H
#define FILE_EDITOR_H

#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>

#include <string.h>
#include <malloc.h>

typedef struct LINE
{
    char *line;
    int size;
    struct LINE *next;
    struct LINE *prev;
} LINE;

void add_symbol(LINE *, char, int, int);

void print_text(LINE *, WINDOW *, int);
void clear_text(WINDOW *, int, int);

void key_backspace(LINE *, WINDOW *);
void key_right(LINE **, WINDOW *, int);
void key_left(LINE **, WINDOW *);
void key_down(LINE **, LINE **, WINDOW *, int, int*, int, int*);
void key_up(LINE **, LINE **, WINDOW *, int, int, int*);

void next_line(LINE *);
void init_page(LINE **, char *);
void load_file(LINE **, char *, int , int *);
void save_file(LINE *, char *);
int file_exists(char *);



#endif