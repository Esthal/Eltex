#include "../FileManager.h"

void move_file(char *cwd_out, char *cwd_in, char *name)
{
    char old_path[PATH_MAX];
    char new_path[PATH_MAX];

    strcpy(old_path, ".");
    strcat(old_path, cwd_out);
    strcat(old_path, "/");
    strcat(old_path, name);

    strcpy(new_path, ".");
    strcat(new_path, cwd_in);
    strcat(new_path, "/");
    strcat(new_path, name);

    move_it(old_path, new_path);
    
}