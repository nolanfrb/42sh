/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handlers
*/

#include "shell.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "line_editing.h"

static void clear_buffer(char *buffer, int capacity)
{
    for (int i = 0; i < capacity; i++)
        buffer[i] = '\0';
}

static void write_prompt(void)
{
    write(STDOUT_FILENO, "\r\033[K$>", 6);
}

static void copy_command_to_buffer(
    const char *command, char *buffer, int *index)
{
    int i = 0;

    while (command[i]) {
        buffer[i] = command[i];
        write(STDOUT_FILENO, &command[i], 1);
        i++;
    }
    *index = i;
}

static bool should_return(shell_t *shell, char **buffer, int *index)
{
    return (!shell || !shell->history || shell->history->count == 0
        || !*buffer || !index);
}

static void update_history_index(shell_t *shell)
{
    if (shell->history_index == shell->history->count)
        shell->history_index = shell->history->count - 1;
    else if (shell->history_index > 0)
        shell->history_index--;
}

static bool reallocate_buffer(char **buffer, int *capacity, int len)
{
    char *new_buf = NULL;

    if (len + 1 < *capacity)
        return true;
    new_buf = realloc(*buffer, len + 1);
    if (!new_buf)
        return false;
    *buffer = new_buf;
    *capacity = len + 1;
    return true;
}

void handle_history_up(shell_t *shell, char **buffer, int *index)
{
    const char *command;
    int len;

    if (should_return(shell, buffer, index))
        return;
    update_history_index(shell);
    command = shell->history->entries[shell->history_index].command;
    if (!command)
        return;
    write_prompt();
    clear_buffer(*buffer, shell->buffer_capacity);
    len = strlen(command);
    if (!reallocate_buffer(buffer, &shell->buffer_capacity, len))
        return;
    copy_command_to_buffer(command, *buffer, index);
}

void handle_history_down(shell_t *shell, char **buffer, int *index)
{
    const char *last_command;
    int len;

    if (should_return(shell, buffer, index))
        return;
    last_command = shell->history->entries[shell->history->count - 1].command;
    if (!last_command)
        return;
    write_prompt();
    clear_buffer(*buffer, shell->buffer_capacity);
    len = strlen(last_command);
    if (!reallocate_buffer(buffer, &shell->buffer_capacity, len))
        return;
    copy_command_to_buffer(last_command, *buffer, index);
}
