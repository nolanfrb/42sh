/*
** EPITECH PROJECT, 2025
** B-PSU-200-NAN-2-1-minishell1-lukas.renaud [WSL: Ubuntu-24.04]
** File description:
** gethostname
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

char *my_gethostname(void)
{
    int fd = open("/etc/hostname", O_RDONLY);
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    char *hostname = NULL;

    if (fd == -1)
        return strdup("");
    if (bytes_read <= 0)
        return strdup("");
    close(fd);
    buffer[bytes_read] = '\0';
    hostname = malloc(bytes_read);
    if (!hostname)
        return strdup("");
    for (ssize_t i = 0; i < bytes_read; i++)
        hostname[i] = buffer[i];
    hostname[bytes_read - 1] = '\0';
    return hostname;
}
