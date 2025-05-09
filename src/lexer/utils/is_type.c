/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_type
*/

#include <stdlib.h>
#include "lexer.h"

bool lexer_token_is_type(token_t *token, token_type_t type)
{
    if (token == NULL)
        return false;
    if (token->type == type)
        return true;
    return false;
}
