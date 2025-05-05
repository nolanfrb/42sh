/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** add_token
*/

#include <stdlib.h>
#include "lexer.h"

static token_t *create_token(token_type_t type, const char *value)
{
    token_t *token = malloc(sizeof(token_t));

    if (token == NULL)
        return NULL;
    token->type = type;
    token->value = strdup(value);
    if (token->value == NULL) {
        free(token);
        return NULL;
    }
    return token;
}

int lexer_add_token(lexer_t *lexer, token_type_t type, const char *value)
{
    token_t *new_token = NULL;

    if (lexer == NULL || value == NULL)
        return -1;
    new_token = create_token(type, value);
    if (new_token == NULL)
        return -1;
    if (chain_add(lexer->tokens, new_token) == -1) {
        free(new_token->value);
        free(new_token);
        return -1;
    }
    lexer->current = new_token;
    lexer->token_count++;
    return 0;
}
