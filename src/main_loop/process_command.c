/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** process_command
*/

#include "ast.h"
#include "command.h"
#include <stdio.h>

int process_command(ast_node_t *ast, shell_t *shell_info)
{
    static int (*execute_functions[])(ast_node_t *, shell_t *) = {
        [NODE_COMMAND] = execute_command,
        [NODE_PIPE] = execute_pipe,
        [NODE_OR] = execute_or,
        [NODE_AND] = execute_and,
        [NODE_SEQUENCE] = execute_sequence,
        [NODE_REDIRECT] = execute_redirect,
    };

    if (ast == NULL)
        return 0;
    return execute_functions[ast->type](ast, shell_info);
}
