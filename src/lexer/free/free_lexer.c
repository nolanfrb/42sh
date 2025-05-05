/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free_lexer
*/

#include <stdlib.h>
#include "lexer.h"

void free_token(token_t *token)
{
    if (token) {
        free(token->value);
        free(token);
    }
}

void free_lexer(lexer_t *lexer)
{
    if (lexer) {
        for (size_t i = 0; i < lexer->token_count; i++) {
            free_token(&lexer->tokens[i]);
        }
        free(lexer->tokens);
        free_token(lexer->current);
        free(lexer);
    }
}
