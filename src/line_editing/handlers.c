/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handlers
*/

#include "shell.h"
#include <unistd.h>
#include <string.h>
#include "line_editing.h"

static void clear_buffer(char *buffer)
{
    for (int i = 0; buffer[i]; i++)
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

void handle_history_up(shell_t *shell, char *buffer, int *index)
{
    const char *command;

    if (!shell || !shell->history || shell->history->count == 0
        || !buffer || !index)
        return;
    if (shell->history_index == shell->history->count)
        shell->history_index = shell->history->count - 1;
    else if (shell->history_index > 0)
        shell->history_index--;
    command = shell->history->entries[shell->history_index].command;
    if (!command)
        return;
    write_prompt();
    clear_buffer(buffer);
    copy_command_to_buffer(command, buffer, index);
}

void handle_history_down(shell_t *shell, char *buffer, int *index)
{
    const char *last_command;

    if (!shell || !shell->history || shell->history->count == 0
        || !buffer || !index)
        return;
    last_command = shell->history->entries[shell->history->count - 1].command;
    if (!last_command)
        return;
    write_prompt();
    clear_buffer(buffer);
    copy_command_to_buffer(last_command, buffer, index);
}
