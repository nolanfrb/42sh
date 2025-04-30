/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** read_command
*/

#include "line_editing.h"
#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>

static void handle_backspace(char *buffer, int *index)
{
    if (*index > 0) {
        (*index)--;
        write(STDOUT_FILENO, "\b \b", 3);
    }
}

static char *resize_buffer(char *buffer, int *capacity)
{
    char *new_buffer;
    int new_capacity = *capacity * 2;

    new_buffer = realloc(buffer, new_capacity);
    if (!new_buffer)
        return NULL;
    *capacity = new_capacity;
    return new_buffer;
}

static bool handle_input_character(
    shell_t *shell_info, char c, char *buffer, int *index)
{
    if (c == 27) {
        handle_escape_sequence(shell_info, buffer, index);
        return true;
    }
    if (c == 127) {
        handle_backspace(buffer, index);
        return true;
    }
    if (c == '\n') {
        write(STDOUT_FILENO, "\n", 1);
        return false;
    }
    buffer[*index] = c;
    (*index)++;
    write(STDOUT_FILENO, &c, 1);
    return true;
}

bool process_character(
    shell_t *shell_info, char **buffer, int *index, int *capacity)
{
    char c;

    if (read(STDIN_FILENO, &c, 1) <= 0)
        return false;
    if (*index + 1 >= *capacity) {
        *buffer = resize_buffer(*buffer, capacity);
        if (!*buffer)
            return false;
    }
    return handle_input_character(shell_info, c, *buffer, index);
}

static char *read_non_interactive_input(bool *had_error)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t len = getline(&line, &size, stdin);

    if (len == -1) {
        *had_error = true;
        free(line);
        return NULL;
    }
    if (line[len - 1] == '\n')
        line[len - 1] = '\0';
    return line;
}

char *read_command_line(shell_t *shell_info, bool *had_error)
{
    int capacity = 16;
    char *buffer = malloc(capacity);
    int index = 0;
    bool reading = true;

    if (!shell_info)
        return NULL;
    if (!isatty(fileno(stdin)))
        return read_non_interactive_input(had_error);
    if (!buffer)
        return NULL;
    while (reading)
        reading = process_character(shell_info, &buffer, &index, &capacity);
    buffer[index] = '\0';
    if (index == 0)
        *had_error = true;
    return buffer;
}
