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

static void close_pipes(int pipes[][2], int count)
{
    for (int i = 0; i < count; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}

static int execute_child_command(command_info_t *command_info, int i,
    shell_t *shell_var)
{
    ast_node_t *node = command_info->commands[i];
    char *full_path = build_path(shell_var, node->data.command->argv[0]);

    if (is_builtin_cmd(node)) {
        free(full_path);
        exit(execute_builtin(node, shell_var));
    }
    if (!full_path) {
        handle_command_not_found(node->data.command->argv[0]);
        exit(1);
    }
    if (command_info->pids[i] == 0) {
        execve(full_path, node->data.command->argv, shell_var->env_array);
        handle_command_not_found(node->data.command->argv[0]);
        exit(1);
    }
    return 1;
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

static void cleanup_command_info(command_info_t *command_info)
{
    free(command_info->commands);
    free(command_info->pipes);
    free(command_info->pids);
    free(command_info);
}

static int wait_for_children(command_info_t *command_info, shell_t *shell_var)
{
    int status = 0;
    int last_status = 0;

    for (int i = 0; i < command_info->command_count; i++) {
        waitpid(command_info->pids[i], &status, 0);
        if ((i == command_info->command_count - 1 && last_status == 0)
        || WEXITSTATUS(status) == 1)
            last_status = WEXITSTATUS(status);
    }
    shell_var->exit_code = last_status;
    return last_status;
}

int execute_pipe(ast_node_t *node, struct shell_s *shell_var)
{
    command_info_t *command_info = malloc(sizeof(command_info_t));
    int last_status;

    if (!command_info)
        return -1;
    if (initialize_command_info(command_info, node) == -1)
        return -1;
    if (setup_pipes_and_fork(command_info, shell_var) == -1) {
        cleanup_command_info(command_info);
        return -1;
    }
    close_pipes(command_info->pipes, command_info->command_count - 1);
    last_status = wait_for_children(command_info, shell_var);
    cleanup_command_info(command_info);
    return last_status;
}
