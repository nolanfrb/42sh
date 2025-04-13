/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_operator
*/

#include "ast.h"
#include <string.h>

bool is_special_op(char *token)
{
    if (!token)
        return false;
    for (int i = 0; SPECIAL_TOKENS[i] != NULL; i++) {
        if (strcmp(token, SPECIAL_TOKENS[i]) == 0)
            return true;
    }
    return false;
}

bool is_redirect_op(char *token)
{
    if (!token)
        return false;
    for (int i = 0; REDIRECTION_TOKENS[i]; i++) {
        if (strcmp(token, REDIRECTION_TOKENS[i]) == 0)
            return true;
    }
    return false;
}
