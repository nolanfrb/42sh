/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_&&_command
*/

#include "ast.h"
#include "command.h"

int execute_and(ast_node_t *ast, shell_t *shell_info)
{
    if (process_command(ast->data.binop.left, shell_info) == 0)
        return process_command(ast->data.binop.right, shell_info);
    return -1;
}
