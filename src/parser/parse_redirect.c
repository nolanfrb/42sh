/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_redirect
*/

#include "ast.h"
#include <stdio.h>
#include <string.h>

const char *REDIRECTION_TOKENS[] = {
    "<",
    ">",
    ">>",
    "<<",
    NULL
};

redirect_type_t get_redirection_type(const char *token)
{
    if (!token)
        return REDIR_NONE;
    if (strcmp(token, "<") == 0)
        return REDIR_IN;
    if (strcmp(token, ">") == 0)
        return REDIR_OUT;
    if (strcmp(token, ">>") == 0)
        return REDIR_APPEND;
    if (strcmp(token, "<<") == 0)
        return REDIR_HEREDOC;
    fprintf(stderr, "error: invalid redirection type\n");
    return REDIR_NONE;
}

ast_node_t *create_redir_node(
    ast_node_t *child, redirect_type_t type, char *filename
)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));

    if (!node) {
        perror("malloc");
        return NULL;
    }
    node->type = NODE_REDIRECT;
    node->data.redir.child = child;
    node->data.redir.type = type;
    node->data.redir.filename = filename;
    return node;
}

int process_redirect_node(ast_node_t **node, char **tokens, int *pos)
{
    char *filename = NULL;
    ast_node_t *redir = NULL;
    redirect_type_t redir_type = get_redirection_type(tokens[*pos]);

    if (redir_type == REDIR_NONE)
        return -1;
    (*pos)++;
    if (!tokens[*pos]) {
        fprintf(stderr, "Missing name for redirect.\n");
        return -1;
    }
    filename = tokens[*pos];
    (*pos)++;
    redir = create_redir_node(*node, redir_type, filename);
    if (!redir) {
        fprintf(stderr, "error: failed to create redirection node\n");
        return -1;
    }
    *node = redir;
    return 0;
}

/**
 * @brief Parses a redirection from the tokens.
 * @todo Handle Memory Management by freeing AST nodes.
 * @param tokens The array of tokens.
 * @param pos The current position in the tokens array.
 * @return The AST node representing the redirection, or NULL on error.
 */
ast_node_t *parse_redirect(char **tokens, int *pos)
{
    ast_node_t *node = parse_subshell(tokens, pos);

    while (tokens[*pos] && is_redirect_op(tokens[*pos])) {
        if (process_redirect_node(&node, tokens, pos) == -1)
            return NULL;
    }
    return node;
}
