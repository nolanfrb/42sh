/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** get_home_directory
*/

#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include "alias.h"

char *get_home_directory(void)
{
    struct passwd *pw = getpwuid(getuid());

    if (!pw) {
        perror("getpwuid");
        return NULL;
    }
    return pw->pw_dir;
}
