/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_subshell
*/

#include "ast.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Check if token is an opening parenthesis
 * @param token The token to check
 * @return true if token is "(", false otherwise
 */
static bool is_subshell_start(const char *token)
{
    return token && strcmp(token, "(") == 0;
}

/**
 * @brief Create a subshell node with the given child node
 * @param child The child node for the subshell
 * @return The created subshell node, or NULL on error
 */
static ast_node_t *create_subshell_node(ast_node_t *child)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));

    if (!node) {
        perror("malloc");
        return NULL;
    }
    node->type = NODE_SUBSHELL;
    node->data.subshell.child = child;
    return node;
}

/**
 * @brief Parse the contents of a subshell
 * @param tokens The token array
 * @param pos The current position in the token array
 * @return The parsed subshell node, or NULL on error
 */
static ast_node_t *handle_subshell_content(char **tokens, int *pos)
{
    ast_node_t *child = parse_sequence(tokens, pos);

    if (!child) {
        fprintf(stderr, "Invalid null command.\n");
        return NULL;
    }
    if (!tokens[*pos] || strcmp(tokens[*pos], ")") != 0) {
        fprintf(stderr, "Too many ('s.\n");
        free(child);
        return NULL;
    }
    (*pos)++;
    return create_subshell_node(child);
}

/**
 * @brief Parse a subshell or command
 * @param tokens The token array
 * @param pos The current position in the token array
 * @return The parsed AST node, or NULL on error
 */
ast_node_t *parse_subshell(char **tokens, int *pos)
{
    if (is_subshell_start(tokens[*pos])) {
        (*pos)++;
        return handle_subshell_content(tokens, pos);
    }
    return parse_command(tokens, pos);
}
