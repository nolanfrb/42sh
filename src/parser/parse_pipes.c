/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_pipes
*/

#include "ast.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static ast_node_t *create_pipe_node(ast_node_t *left, ast_node_t *right)
{
    ast_node_t *pipe = malloc(sizeof(ast_node_t));

    if (!pipe) {
        perror("malloc");
        return NULL;
    }
    pipe->type = NODE_PIPE;
    pipe->data.binop.left = left;
    pipe->data.binop.right = right;
    return pipe;
}

ast_node_t *parse_pipes(char **tokens, int *pos)
{
    ast_node_t *left = parse_redirect(tokens, pos);
    ast_node_t *right = NULL;

    while (tokens[*pos] && strcmp(tokens[*pos], "|") == 0) {
        (*pos)++;
        right = parse_redirect(tokens, pos);
        if (!right)
            return NULL;
        left = create_pipe_node(left, right);
        if (!left)
            return NULL;
    }
    return left;
}
