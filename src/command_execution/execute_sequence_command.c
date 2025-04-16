/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_sequence
*/

#include "ast.h"
#include "command.h"

int execute_sequence(ast_node_t *ast, shell_t *shell_info)
{
    process_command(ast->data.binop.left, shell_info);
    return process_command(ast->data.binop.right, shell_info);
}
