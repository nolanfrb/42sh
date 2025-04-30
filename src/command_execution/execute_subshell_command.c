/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_subshell_command
*/

#include "command.h"
#include "shell.h"
#include "ast.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int execute_subshell_command(ast_node_t *ast, shell_t *shell_var)
{
    int exit_code = 0;
    ast_node_t *subshell = ast->data.binop.left;
    pid_t pid = fork();

    if (subshell == NULL)
        return 0;
    if (pid == -1)
        return -1;
    if (pid == 0)
        exit(process_command(subshell, shell_var));
    waitpid(pid, &exit_code, 0);
    if (WIFEXITED(exit_code))
        exit_code = WEXITSTATUS(exit_code);
    else if (WIFSIGNALED(exit_code)) {
        handle_exit_status(exit_code);
        exit_code = 128 + WTERMSIG(exit_code);
    }
    shell_var->exit_code = exit_code;
    return shell_var->exit_code;
}
