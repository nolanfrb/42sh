/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** handle_parenthesis
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int handle_left_parenthesis(lexer_t *lexer)
{
    return lexer_add_token(lexer, TOKEN_LPAREN, "(");
}

int handle_right_parenthesis(lexer_t *lexer)
{
    return lexer_add_token(lexer, TOKEN_RPAREN, ")");
}
