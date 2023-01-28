#include "../FileManager.h"

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