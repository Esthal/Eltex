#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <curses.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


#include <string.h>
#include <malloc.h>

typedef struct ManagerDir
{
    char *name;
    long int size;
    struct ManagerDir *next;
    struct ManagerDir *prev;
} ManagerDir;

typedef struct WinSize
{
    unsigned int padding_x;
    unsigned int padding_y;
    unsigned int x;
    unsigned int y;
} WinSize;

void add_dir(ManagerDir **, char *, long int);
void clean_dir(ManagerDir **);
void read_dir(char *, ManagerDir **);
void print_dir(ManagerDir *, WINDOW *, WinSize *, int);
void goto_dir(ManagerDir **, ManagerDir *, char *);

void set_cwd(char *);
void print_pwd(WINDOW *, char *, int);

void print_line(WINDOW *, char *, int);
void set_window_size(WinSize *, int , int , int , int);
void clear_screen(WINDOW *, WinSize);

void move_it(char *, char *);
void refresh_list(ManagerDir **, char *);
void create_file(char *, char *);
void delete_file(char *, char *);
void move_file(char *, char *, char *);
void copy_file(char *, char *);
char *get_string(WINDOW *, WinSize);
void rename_file(char *, char *, char *);

#endif