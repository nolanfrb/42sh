/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** setup
*/

#include "command.h"
#include "shell.h"
#include "ast.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void setup_pipes(pipe_state_t *state, int idx, int count)
{
    state->curr[0] = -1;
    state->curr[1] = -1;
    if (idx < count - 1) {
        if (pipe(state->curr) == -1) {
            perror("pipe");
            close_parent_pipes(state->prev);
            exit(1);
        }
    }
}

void setup_child_pipes(int prev_pipe[2], int curr_pipe[2])
{
    if (prev_pipe[0] != -1) {
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
    }
    if (prev_pipe[1] != -1)
        close(prev_pipe[1]);
    if (curr_pipe[1] != -1) {
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[1]);
    }
    if (curr_pipe[0] != -1)
        close(curr_pipe[0]);
}

void close_parent_pipes(int prev_pipe[2])
{
    if (prev_pipe[0] != -1)
        close(prev_pipe[0]);
    if (prev_pipe[1] != -1)
        close(prev_pipe[1]);
}

int create_pipe_if_needed(int curr_pipe[2], int prev_pipe[2], int i,
    int command_count)
{
    curr_pipe[0] = -1;
    curr_pipe[1] = -1;
    if (i < command_count - 1) {
        if (pipe(curr_pipe) == -1) {
            perror("pipe");
            close_parent_pipes(prev_pipe);
            return -1;
        }
    }
    return 0;
}

int setup_pipes_and_fork(command_info_t *info, shell_t *shell)
{
    pipe_state_t state = {{-1, -1}, {-1, -1}};
    int result = 0;

    for (int i = 0; i < info->command_count; i++) {
        result = process_pipe_command(info, i, shell, &state);
        if (result != 0) {
            return result;
        }
    }
    close_parent_pipes(state.prev);
    return 0;
}
