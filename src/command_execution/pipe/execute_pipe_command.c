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
#include "globbings.h"

static int execute_child_command(command_info_t *command_info, int i,
    shell_t *shell_var)
{
    ast_node_t *node = command_info->commands[i];
    char *full_path = build_path(shell_var, node->data.command->argv[0]);
    int return_value = 0;

    if (!full_path) {
        handle_command_not_found(node->data.command->argv[0]);
        exit(1);
    }
    if (command_info->pids[i] == 0) {
        if (is_builtin_cmd(node)) {
            return_value = execute_builtin(node, shell_var);
            free(full_path);
            exit(return_value);
        }
        globbings(node);
        execve(full_path, node->data.command->argv, shell_var->env_array);
        handle_command_not_found(node->data.command->argv[0]);
        exit(1);
    }
    return 1;
}

static int handle_fork_error(int prev_pipe[2], int curr_pipe[2])
{
    perror("fork");
    close_parent_pipes(prev_pipe);
    if (curr_pipe[0] != -1)
        close(curr_pipe[0]);
    if (curr_pipe[1] != -1)
        close(curr_pipe[1]);
    return -1;
}

static int handle_special_command(ast_node_t *node, shell_t *shell_var)
{
    if (node->type == NODE_SUBSHELL) {
        execute_subshell_command(node, shell_var);
        return 1;
    }
    if (node->type == NODE_REDIRECT) {
        execute_redirect(node, shell_var);
        return 1;
    }
    return 0;
}

static void handle_child(command_info_t *info, int idx, shell_t *shell)
{
    ast_node_t *node = info->commands[idx];

    if (handle_special_command(node, shell) == 1) {
        exit(0);
    }
    execute_child_command(info, idx, shell);
}

static int create_child_process(command_info_t *info, int idx,
    shell_t *shell, pipe_state_t *state)
{
    info->pids[idx] = fork();
    if (info->pids[idx] == -1) {
        return handle_fork_error(state->prev, state->curr);
    }
    if (info->pids[idx] == 0) {
        setup_child_pipes(state->prev, state->curr);
        handle_child(info, idx, shell);
    }
    return 0;
}

static void update_pipe_state(pipe_state_t *state)
{
    close_parent_pipes(state->prev);
    state->prev[0] = state->curr[0];
    state->prev[1] = state->curr[1];
}

int process_pipe_command(command_info_t *info, int idx,
    shell_t *shell, pipe_state_t *state)
{
    setup_pipes(state, idx, info->command_count);
    if (create_child_process(info, idx, shell, state) != 0) {
        return -1;
    }
    update_pipe_state(state);
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
    last_status = wait_for_children(command_info, shell_var);
    cleanup_command_info(command_info);
    return last_status;
}
