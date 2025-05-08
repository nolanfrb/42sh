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

void lexer_destroy(lexer_t *lexer)
{
}
