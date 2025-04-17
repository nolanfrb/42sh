/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_command
*/

#include "ast.h"
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

static void child_process(
    char *full_path, ast_node_t *node, struct shell_s *shell_var)
{
    execve(full_path, node->data.command->argv, shell_var->env_array);
    handle_command_not_found(node->data.command->argv[0]);
}

int execute_command(ast_node_t *node, struct shell_s *shell_var)
{
    const builtin_t *builtins = get_builtins();
    pid_t pid;
    int status;
    char *full_path = build_path(shell_var, node->data.command->argv[0]);

    for (int i = 0; builtins[i].name != NULL; i++) {
        if (strcmp(node->data.command->argv[0], builtins[i].name) == 0)
            return builtins[i].func(shell_var, node->data.command->argv);
    }
    pid = fork();
    if (pid == 0)
        child_process(full_path, node, shell_var);
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        handle_exit_status(status);
        return 128 + WTERMSIG(status);
    }
    return 0;
}
