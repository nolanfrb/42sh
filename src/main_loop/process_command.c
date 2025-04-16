/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** process_command
*/

#include "ast.h"
#include <stdio.h>

void process_command(ast_node_t *ast, shell_t *shell_info)
{
    static int (*execute_functions[])(ast_node_t *, shell_t *) = {
        [NODE_COMMAND] = execute_command,
    };

    execute_functions[ast->type](ast, shell_info);
}
