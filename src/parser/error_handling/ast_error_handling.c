/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** ast_error_handling
*/

#include <stdio.h>
#include "ast.h"
#include "shell.h"

int ast_error_handling(ast_node_t *node)
{
    int status = 0;

    if (!node)
        return -1;
    if (node->type == NODE_AND || node->type == NODE_OR)
        status = and_or_error_handling(node);
    return status;
}
