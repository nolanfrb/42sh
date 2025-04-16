/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** error_handling_and_or
*/

#include <stdio.h>
#include "shell.h"
#include "ast.h"


int and_or_error_handling(ast_node_t *node)
{
    int status = 0;

    if (node == NULL) {
        fprintf(stderr, "Error: Node is NULL\n");
        return -1;
    }
    if (node->type != NODE_AND && node->type != NODE_OR) {
        fprintf(stderr, "Error: Invalid node type\n");
        return -1;
    }
    if (node->data.binop.left == NULL || node->data.binop.right == NULL) {
        fprintf(stderr, "Invalid null command.\n");
        return -1;
    }
    if (node->data.binop.left != NULL) {
        status = ast_error_handling(node->data.binop.left);
        if (status != 0)
            return status;
    }
    if (node->data.binop.right != NULL) {
        status = ast_error_handling(node->data.binop.right);
    }
    return 0;
}
