/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** token_matching
*/

#include <stdlib.h>
#include "lexer.h"

bool lexer_match_token(lexer_t *lexer, token_type_t type, const char *value)
{
    if (lexer == NULL || lexer->current == NULL)
        return false;
    if (lexer->current->type == type && lexer->current->value != NULL &&
        strcmp(lexer->current->value, value) == 0)
        return true;
    return false;
}
