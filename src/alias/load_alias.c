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
        return -1;
    }
    return fd;
}

alias_t *load_alias(void)
{
    alias_t *alias = NULL;
    int fd = open_alias_file();

    if (fd == -1)
        return NULL;
    alias = init_alias(count_aliases(fd));
    if (!alias) {
        close(fd);
        free_alias(alias);
        return NULL;
    }
    alias->info = parse_alias_file(fd, alias);
    if (close(fd) == -1)
        return NULL;
    if (!alias->info) {
        free_alias(alias);
        fprintf(stderr, "Error loading alias file\n");
        return NULL;
    }
    return alias;
}
