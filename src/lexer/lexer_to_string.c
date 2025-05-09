/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** lexer_to_string
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static void free_tokens(char **array, int start_index, int end_index)
{
    for (int i = start_index; i < end_index; i++) {
        free(array[i]);
    }
    free(array);
}

char **lexer_to_strings(lexer_t *lexer)
{
    char **tokens = malloc(sizeof(char *) * lexer->token_count + 1);
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
    tokens[lexer->token_count] = NULL;
    return tokens;
}
