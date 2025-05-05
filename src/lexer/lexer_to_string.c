/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** lexer_to_string
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static void free_tokens(char **array, int token_count, int index)
{
    while (++index < token_count)
        free(array[index]);
    free(array);
}

char **lexer_to_strings(lexer_t *lexer)
{
    char **tokens = malloc(sizeof(char *) * lexer->token_count);
    chain_node_t *current = lexer->tokens->tail;
    int i = lexer->token_count - 1;
    token_t *token = NULL;

    if (!tokens)
        return NULL;
    while (current != NULL && i >= 0) {
        token = (token_t *)current->data;
        tokens[i] = strdup(token->value);
        if (!tokens[i]) {
            free_tokens(tokens, lexer->token_count, i);
            return NULL;
        }
        current = current->prev;
        i--;
    }
    return tokens;
}