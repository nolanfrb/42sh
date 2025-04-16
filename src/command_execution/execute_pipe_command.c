/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_pipe_command
*/

#include "command.h"
#include "shell.h"
#include "ast.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

static int count_pipe_commands(ast_node_t *node)
{
    int count = 1;
    ast_node_t *current = node;

    while (current->type == NODE_PIPE && current->data.binop.right) {
        count++;
        current = current->data.binop.right;
    }
    return count;
}

static void fill_pipe_commands(ast_node_t *node, ast_node_t **commands,
    int count)
{
    ast_node_t *current = node;
    int i = 0;

    commands[i] = current->data.binop.left;
    i++;
    while (current->type == NODE_PIPE && current->data.binop.right &&
        i < count) {
        if (current->data.binop.right->type == NODE_PIPE) {
            commands[i] = current->data.binop.right->data.binop.left;
            i++;
        } else {
            commands[i] = current->data.binop.right;
            i++;
        }
        current = current->data.binop.right;
    }
}

static ast_node_t **collect_pipe_commands(ast_node_t *node, int *count)
{
    ast_node_t **commands;

    *count = count_pipe_commands(node);
    commands = malloc(sizeof(ast_node_t *) * (*count));
    if (!commands)
        return NULL;
    fill_pipe_commands(node, commands, *count);
    return commands;
}

static void close_pipes(int pipes[][2], int count)
{
    for (int i = 0; i < count; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}

static int execute_child_command(command_info_t *command_info, int i,
    struct shell_s *shell_var)
{
    if (is_builtin_cmd(command_info->commands[i]))
        return -1;
    if (command_info->pids[i] == 0) {
        execve(command_info->commands[i]->data.command->argv[0],
            command_info->commands[i]->data.command->argv,
            shell_var->env_array);
        handle_command_not_found
        (command_info->commands[i]->data.command->argv[0]);
    }
    return -1;
}

static void handle_child_process(int i, command_info_t *command_info,
    struct shell_s *shell_var)
{
    if (i > 0)
        dup2(command_info->pipes[i - 1][0], STDIN_FILENO);
    if (i < command_info->command_count - 1)
        dup2(command_info->pipes[i][1], STDOUT_FILENO);
    close_pipes(command_info->pipes, command_info->command_count - 1);
    execute_child_command(command_info, i, shell_var);
    exit(1);
}

static int setup_pipes_and_fork(command_info_t *command_info,
    struct shell_s *shell_var)
{
    for (int i = 0; i < command_info->command_count - 1; i++) {
        if (pipe(command_info->pipes[i]) == -1) {
            perror("pipe");
            return -1;
        }
    }
    for (int i = 0; i < command_info->command_count; i++) {
        command_info->pids[i] = fork();
        if (command_info->pids[i] == -1) {
            perror("fork");
            close_pipes(command_info->pipes, command_info->command_count - 1);
            return -1;
        }
        if (command_info->pids[i] == 0)
            handle_child_process(i, command_info, shell_var);
    }
    return 0;
}

static int initialize_command_info(command_info_t *command_info,
    ast_node_t *node)
{
    command_info->command_count = 0;
    command_info->commands = collect_pipe_commands(node,
        &command_info->command_count);
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

static void cleanup_command_info(command_info_t *command_info)
{
    free(command_info->commands);
    free(command_info->pipes);
    free(command_info->pids);
    free(command_info);
}

int execute_pipe(ast_node_t *node, struct shell_s *shell_var)
{
    command_info_t *command_info = malloc(sizeof(command_info_t));
    int status = 0;

    if (!command_info)
        return -1;
    if (initialize_command_info(command_info, node) == -1)
        return -1;
    if (setup_pipes_and_fork(command_info, shell_var) == -1) {
        cleanup_command_info(command_info);
        return -1;
    }
    waitpid(command_info->pids[command_info->command_count], &status, 0);
    close_pipes(command_info->pipes, command_info->command_count - 1);
    cleanup_command_info(command_info);
    return 0;
}
