/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** pipe_error_handling
*/

#include <stdio.h>
#include "ast.h"

int pipe_error_handling(ast_node_t *node)
{
    if (!node)
        return -1;
    if (!node->data.binop.left || !node->data.binop.right) {
        fprintf(stderr, "Invalid null command.\n");
        return -1;
    }
    return 0;
}
