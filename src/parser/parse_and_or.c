/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_and_or
*/

#include "ast.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Check if token is an AND/OR operator
 * @param token The token to check
 * @return true if token is "&&" or "||", false otherwise
 */
static bool is_and_or_operator(const char *token)
{
    return token && (strcmp(token, "&&") == 0 || strcmp(token, "||") == 0);
}

/**
 * @brief Get the node type for an AND/OR operator
 * @param token The operator token ("&&" or "||")
 * @return The corresponding node type (NODE_AND or NODE_OR)
 */
static node_type_t get_operator_type(const char *token)
{
    return (strcmp(token, "&&") == 0) ? NODE_AND : NODE_OR;
}

/**
 * @brief Create a binary operation node
 * @param type The type of operation (NODE_AND or NODE_OR)
 * @param left The left operand
 * @param right The right operand
 * @return The created binary operation node, or NULL on error
 */
ast_node_t *create_binop_node(
    node_type_t type, ast_node_t *left, ast_node_t *right
)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));

    if (!node) {
        perror("malloc");
        return NULL;
    }
    node->type = type;
    node->data.binop.left = left;
    node->data.binop.right = right;
    return node;
}

/**
 * @brief Parse AND/OR operations
 * @param tokens The token array
 * @param pos Pointer to the current position in the token array
 * @return The parsed AST node, or NULL on error
 */
ast_node_t *parse_and_or_recursive(ast_node_t *left, char **tokens, int *pos)
{
    ast_node_t *right = NULL;
    ast_node_t *and_or = NULL;
    node_type_t type;

    while (tokens[*pos] && is_and_or_operator(tokens[*pos])) {
        type = get_operator_type(tokens[*pos]);
        (*pos)++;
        right = parse_pipes(tokens, pos);
        if (!right) {
            fprintf(stderr, "Invalid null command.\n");
            return NULL;
        }
        and_or = create_binop_node(type, left, right);
        if (!and_or)
            return NULL;
        left = and_or;
    }
    return left;
}

ast_node_t *parse_and_or(char **tokens, int *pos)
{
    ast_node_t *left = parse_pipes(tokens, pos);

    if (!left) {
        fprintf(stderr, "Invalid null command.\n");
        return NULL;
    }
    return parse_and_or_recursive(left, tokens, pos);
}
