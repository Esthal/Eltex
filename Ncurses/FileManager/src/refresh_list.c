#include "../FileManager.h"

void refresh_list(ManagerDir **list, char *cwd)
{
    clean_dir(list);
    read_dir(cwd, list);
}