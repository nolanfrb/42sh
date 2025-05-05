/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** free_ast
*/

#include "ast.h"

static void free_ast_command(ast_node_t *node)
{
    if (node->data.command == NULL)
        return;
    free(node->data.command->argv);
    free(node->data.command);
}

static void free_ast_children(ast_node_t *node)
{
    if (node->type == NODE_PIPE || node->type == NODE_SEQUENCE ||
        node->type == NODE_AND || node->type == NODE_OR) {
        free_ast(node->data.binop.left);
        free_ast(node->data.binop.right);
    }
    if (node->type == NODE_REDIRECT)
        free_ast(node->data.redir.child);
    if (node->type == NODE_SUBSHELL)
        free_ast(node->data.subshell.child);
}

void free_ast(ast_node_t *node)
{
    if (node == NULL)
        return;
    if (node->type == NODE_COMMAND)
        free_ast_command(node);
    else
        free_ast_children(node);
    free(node);
}
