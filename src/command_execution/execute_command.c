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
#include "globbings.h"

static void child_process(
    char *full_path, ast_node_t *node, struct shell_s *shell_var)
{
    execve(full_path, node->data.command->argv, shell_var->env_array);
    handle_command_not_found(node->data.command->argv[0]);
    shell_var->exit_code = 1;
    exit(1);
}

int execute_builtin(ast_node_t *node, struct shell_s *shell_var)
{
    const builtin_t *builtins = get_builtins();

    for (int i = 0; builtins[i].name != NULL; i++) {
        if (strcmp(node->data.command->argv[0], builtins[i].name) == 0)
            return builtins[i].func(shell_var, node->data.command->argv);
    }
    return -1;
}

static int execute_external_command(
    char *full_path, ast_node_t *node, struct shell_s *shell_var)
{
    pid_t pid = fork();
    int status;

    if (pid == -1) {
        perror("fork failed");
        return -1;
    }
    if (pid == 0) {
        child_process(full_path, node, shell_var);
        exit(1);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        handle_exit_status(status);
        return 128 + WTERMSIG(status);
    }
    return 0;
}

int execute_command(ast_node_t *node, struct shell_s *shell_var)
{
    char *full_path = build_path(shell_var, node->data.command->argv[0]);
    int result = execute_builtin(node, shell_var);

    if (shell_var->alias->state == DEFAULT)
        return search_alias(shell_var->alias, node->data.command, shell_var);
    else {
        if (result != -1) {
            free(full_path);
            return result;
        }
        globbings(node);
        result = execute_external_command(full_path, node, shell_var);
        free(full_path);
        return result;
    }
    return 0;
}
