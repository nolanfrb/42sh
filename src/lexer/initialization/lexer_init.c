/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** init_lexer
*/

#include <stdlib.h>
#include "lexer.h"

token_t *token_create_default(void)
{
    token_t *token = malloc(sizeof(token_t));

    if (!token)
        return NULL;
    token->type = TOKEN_END;
    token->value = NULL;
    return token;
}

lexer_t *lexer_init(const char *input, shell_t *shell)
{
    lexer_t *lexer = malloc(sizeof(lexer_t));

    if (!lexer)
        return NULL;
    lexer->input = (char *)input;
    lexer->pos = 0;
    lexer->token_count = 0;
    lexer->tokens = chain_create();
    if (!lexer->tokens) {
        free(lexer);
        return NULL;
    }
    lexer->current = token_create_default();
    if (!lexer->current) {
        free(lexer);
        return NULL;
    }
    lexer->shell = shell;
    return lexer;
}
