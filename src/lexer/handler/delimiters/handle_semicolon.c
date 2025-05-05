/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** handle_semicolon
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int handle_semicolon(lexer_t *lexer)
{
    return lexer_add_token(lexer, TOKEN_SEMICOLON, ";");
}
