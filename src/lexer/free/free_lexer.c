/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free_lexer
*/

#include <stdlib.h>
#include "lexer.h"

static void free_token_value(void *token)
{
    token_t *t = (token_t *)token;

    if (t != NULL && t->value != NULL)
        free(t->value);
}

void lexer_destroy(lexer_t *lexer)
{
    if (lexer == NULL)
        return;
    if (lexer->tokens != NULL) {
        chain_iterate(lexer->tokens, free_token_value);
        chain_destroy(lexer->tokens);
    }
    if (lexer->input != NULL)
        free(lexer->input);
    free(lexer);
}