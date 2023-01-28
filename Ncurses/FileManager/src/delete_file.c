#include "../FileManager.h"

void delete_file(char *cwd, char *name)
{
    char path[PATH_MAX];
    strcpy(path, ".");
    strcat(path, cwd);
    strcat(path, "/");
    strcat(path, name);
    remove(path);
}