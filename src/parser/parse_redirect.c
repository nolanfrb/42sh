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
    if (strcmp(token, "<") == 0)
        return REDIR_IN;
    if (strcmp(token, ">") == 0)
        return REDIR_OUT;
    if (strcmp(token, ">>") == 0)
        return REDIR_APPEND;
    if (strcmp(token, "<<") == 0)
        return REDIR_HEREDOC;
    return REDIR_NONE;
}

ast_node_t *create_redir_node(ast_node_t *child, redirect_type_t type, char *filename)
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
    redirect_type_t redir_type;
    ast_node_t *redir = NULL;
    char *filename = NULL;

    if (!node)
        return NULL;
    while (tokens[*pos] && is_redirect_op(tokens[*pos])) {
        redir_type = get_redirection_type(tokens[*pos]);
        (*pos)++;
        
        if (!tokens[*pos]) {
            fprintf(stderr, "error: missing filename for redirection\n");
            return NULL;
        }
        filename = tokens[*pos];
        (*pos)++;
        redir = create_redir_node(node, redir_type, filename);
        if (!redir)
            return NULL;
        node = redir;
    }
    return node;
}
