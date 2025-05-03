/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** parse_alias_file
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "alias.h"

static alias_info_t **process_alias_lines(FILE *file, alias_t *alias)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    for (int i = 0; i < alias->nb_alias; i++) {
        read = getline(&line, &len, file);
        if (read == -1) {
            perror("getline");
            free(line);
            return NULL;
        }
        extract_alias(line, alias->info[i]);
        if (!alias->info[i]) {
            perror("strdup");
            free(line);
            return NULL;
        }
    }
    free(line);
    return alias->info;
}

alias_info_t **parse_alias_file(int fd, alias_t *alias)
{
    FILE *file = fdopen(dup(fd), "r");
    alias_info_t **result = NULL;

    if (!file)
        return NULL;
    result = process_alias_lines(file, alias);
    fclose(file);
    return result;
}
