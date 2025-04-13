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

ast_node_t *parse_pipes(char **tokens, int *pos)
{
    ast_node_t *left = parse_redirect(tokens, pos);
    ast_node_t *right = NULL;
    ast_node_t *pipe = malloc(sizeof(ast_node_t));

    if (!pipe) {
        perror("malloc");
        return NULL;
    }
    while (tokens[*pos] && strcmp(tokens[*pos], "|") == 0) {
        (*pos)++;
        right = parse_redirect(tokens, pos);
        pipe->type = NODE_PIPE;
        pipe->data.binop.left = left;
        pipe->data.binop.right = right;
        left = pipe;
    }
    return left;
}
