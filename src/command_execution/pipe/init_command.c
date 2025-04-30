/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** init_command
*/

#include "command.h"
#include "ast.h"
#include <stdlib.h>

int initialize_command_info(command_info_t *command_info,
    ast_node_t *node)
{
    command_info->command_count = 0;
    command_info->commands = collect_pipe_commands
    (node, &command_info->command_count);
    if (!command_info->commands)
        return -1;
    command_info->pipes = malloc(sizeof(int[2]) *
    (command_info->command_count - 1));
    if (!command_info->pipes) {
        free(command_info->commands);
        return -1;
    }
    command_info->pids = malloc(sizeof(pid_t) * command_info->command_count);
    if (!command_info->pids) {
        free(command_info->pipes);
        free(command_info->commands);
        return -1;
    }
    return 0;
}
