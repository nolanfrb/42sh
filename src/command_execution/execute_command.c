/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_command
*/

#include "shell.h"
#include "command.h"
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>

int execute_command(ast_node_t *node, struct shell_s *shell_var)
{
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        execve(node->data.command.argv[0], node->data.command.argv,
            shell_var->env);
        handle_command_not_found(node->data.command.argv[0]);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        handle_exit_status(status);
        return 128 + WTERMSIG(status);
    }
    return -1;
}
