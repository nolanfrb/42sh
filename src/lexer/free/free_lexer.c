/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free_lexer
*/

#include <stdlib.h>
#include "lexer.h"

static void free_token_node(chain_node_t *node)
{
    token_t *token;

    if (!node || !node->data)
        return;
    token = (token_t *)node->data;
    if (token->value)
        free(token->value);
    free(token);
    free(node);
}

static void destroy_token_list(chain_t *list)
{
    chain_node_t *current;
    chain_node_t *next;

    if (!list)
        return;
    current = list->head;
    while (current) {
        next = current->next;
        free_token_node(current);
        current = next;
    }
    free(list);
}

void lexer_destroy(lexer_t *lexer)
{
    if (!lexer)
        return;
    if (lexer->tokens)
        destroy_token_list(lexer->tokens);
    free(lexer);
}
