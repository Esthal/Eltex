#include "../FileManager.h"

void rename_file(char *cwd, char *old_name, char *new_name)
{
    char old_path[PATH_MAX];
    char new_path[PATH_MAX];

    strcpy(old_path, ".");
    strcat(old_path, cwd);
    strcat(old_path, "/");
    strcat(old_path, old_name);

    strcpy(new_path, ".");
    strcat(new_path, cwd);
    strcat(new_path, "/");
    strcat(new_path, new_name);

    move_it(old_path, new_path);
}