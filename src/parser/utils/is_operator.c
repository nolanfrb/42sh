/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_operator
*/

#include "ast.h"
#include <string.h>

bool is_operator(char *token)
{
    for (int i = 0; SPECIAL_TOKENS[i] != NULL; i++) {
        if (strcmp(token, SPECIAL_TOKENS[i]) == 0)
            return true;
    }
    return false;
}