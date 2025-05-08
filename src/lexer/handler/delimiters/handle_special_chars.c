/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** handle_special_chars
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int handle_pipe(lexer_t *lexer)
{
    if (lexer->input[lexer->pos + 1] == '|') {
        lexer->pos += 2;
        return lexer_add_token(lexer, TOKEN_OR, "||");
    }
    lexer->pos++;
    return lexer_add_token(lexer, TOKEN_PIPE, "|");
}

int handle_and(lexer_t *lexer)
{
    if (lexer->input[lexer->pos + 1] == '&') {
        lexer->pos += 2;
        return lexer_add_token(lexer, TOKEN_AND, "&&");
    }
    lexer->pos++;
    return handle_word(lexer);
}

int handle_redirect_in(lexer_t *lexer)
{
    if (lexer->input[lexer->pos + 1] == '<') {
        lexer->pos += 2;
        return lexer_add_token(lexer, TOKEN_HEREDOC, "<<");
    }
    lexer->pos++;
    return lexer_add_token(lexer, TOKEN_REDIRECT_IN, "<");
}

int handle_redirect_out(lexer_t *lexer)
{
    if (lexer->input[lexer->pos + 1] == '>') {
        lexer->pos += 2;
        return lexer_add_token(lexer, TOKEN_APPEND_OUT, ">>");
    }
    lexer->pos++;
    return lexer_add_token(lexer, TOKEN_REDIRECT_OUT, ">");
}

int handle_semicolon(lexer_t *lexer)
{
    lexer->pos++;
    return lexer_add_token(lexer, TOKEN_SEMICOLON, ";");
}
