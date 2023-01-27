#include "../FileManager.h"

void set_cwd(char *cwd)
{
    if (getcwd(cwd, PATH_MAX) == NULL) {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
}