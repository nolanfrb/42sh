/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** path
*/

#include "shell.h"
#include "command.h"
#include <string.h>
#include "env.h"

char *get_path(char **env)
{
    char *path = my_getenv("PATH", env);

    if (!path)
        path = DEFAULT_PATH;
    return path;
}
