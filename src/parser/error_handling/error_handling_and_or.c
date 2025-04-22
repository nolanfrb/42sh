/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** error_handling_and_or
*/

#include <stdio.h>
#include "shell.h"
#include "ast.h"


static int validate_and_or_node(ast_node_t *node)
{
    if (!node) {
        fprintf(stderr, "Error: Node is NULL\n");
        return -1;
    }
    if (node->type != NODE_AND && node->type != NODE_OR) {
        fprintf(stderr, "Error: Invalid node type\n");
        return -1;
    }
    if (!node->data.binop.left || !node->data.binop.right) {
        fprintf(stderr, "Invalid null command.\n");
        return -1;
    }
    return 0;
}

int and_or_error_handling(ast_node_t *node)
{
    int status = validate_and_or_node(node);

    if (status != 0)
        return status;
    if (node->data.binop.left) {
        status = ast_error_handling(node->data.binop.left);
        if (status != 0)
            return status;
    }
    if (node->data.binop.right)
        status = ast_error_handling(node->data.binop.right);
    return 0;
}
