/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** load_alias
*/

#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <regex.h>
#include "alias.h"

static int open_alias_file(void)
{
    char *home = get_home_directory();
    int fd;
    struct stat st;

    if (!home)
        return -1;
    fd = open(strcat(home, "/.42shrc"), O_RDONLY | O_CREAT, 0644);
    if (fd == -1)
        return -1;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        return -1;
    }
    if (st.st_size == 0) {
        close(fd);
        return -2;
    }
    return fd;
}

static alias_t *init_alias_from_file(int fd)
{
    int alias_count = count_aliases(fd);
    alias_t *alias = init_alias(alias_count);
    int close_status = 0;

    if (alias == NULL)
        return NULL;
    alias->info = parse_alias_file(fd, alias);
    close_status = close(fd);
    if (alias->info == NULL || close_status == -1) {
        free_alias(alias);
        return NULL;
    }
    return alias;
}

alias_t *load_alias(void)
{
    alias_t *alias = NULL;
    int fd = 0;

    fd = open_alias_file();
    if (fd == -1)
        return NULL;
    if (fd == -2) {
        close(fd);
        alias = init_alias(0);
        if (alias == NULL)
            return NULL;
        return alias;
    }
    alias = init_alias_from_file(fd);
    return alias;
}
