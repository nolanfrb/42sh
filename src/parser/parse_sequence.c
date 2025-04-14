/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_sequence
*/

#include "ast.h"
#include <string.h>
#include <stdio.h>

ast_node_t *parse_sequence(char **tokens, int *pos)
{
    ast_node_t *left = parse_and_or(tokens, pos);
    ast_node_t *right = NULL;
    ast_node_t *seq = malloc(sizeof(ast_node_t));

    if (!seq) {
        perror("malloc");
        return NULL;
    }
    while (tokens[*pos] && strcmp(tokens[*pos], ";") == 0) {
        (*pos)++;
        right = parse_and_or(tokens, pos);
        seq = create_binop_node(NODE_SEQUENCE, left, right);
        if (!seq)
            return NULL;
        left = seq;
    }
    return left;
}
