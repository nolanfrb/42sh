/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** count_aliases
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "alias.h"

int count_aliases(int fd)
{
    FILE *file = fdopen(dup(fd), "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int count = 0;

    if (!file)
        return 0;
    read = getline(&line, &len, file);
    while (read != -1) {
        if (line[0] != '\n') {
            count++;
        }
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    lseek(fd, 0, SEEK_SET);
    return count;
}
