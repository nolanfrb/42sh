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

void handle_history_up(shell_t *shell)
{
    const char *last_command;

    if (!shell || !shell->history || shell->history->count == 0)
        return;
    last_command = shell->history->entries[shell->history->count - 1].command;
    if (last_command)
        write(STDOUT_FILENO, last_command, strlen(last_command));
}

void handle_history_down(shell_t *shell)
{
    const char *last_command;

    if (!shell || !shell->history || shell->history->count == 0)
        return;
    last_command = shell->history->entries[shell->history->count - 1].command;
    if (last_command)
        write(STDOUT_FILENO, last_command, strlen(last_command));
}
