/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** handle_backslash
*/

#include "inhibitors.h"
#include "lexer.h"

static int handle_backslash(lexer_t *lexer)
{
    if (lexer->input[lexer->pos] == BACKSLASH) {
        if (lexer->input[lexer->pos + 1] == '\0')
            return 0;
        lexer->pos++;
        return 1;
    }
    return 0;
}

int handle_quote(lexer_t *lexer, char quote_type)
{
    lexer->pos++;
    while (lexer->input[lexer->pos] != '\0') {
        if (lexer->input[lexer->pos] == quote_type)
            break;
        if (quote_type == DOUBLE_QUOTE && handle_backslash(lexer))
            continue;
        lexer->pos++;
    }
    if (lexer->input[lexer->pos] == '\0')
        return -1;
    return 0;
}

int handle_inhibitor(lexer_t *lexer)
{
    char c = lexer->input[lexer->pos];

    if (handle_backslash(lexer) != 0)
        return -1;
    if (c == SIMPLE_QUOTE || c == DOUBLE_QUOTE) {
        if (lexer->start != lexer->pos && handle_word(lexer) != 0)
            return -1;
        lexer->start = lexer->pos;
        if (handle_quote(lexer, c) != 0)
            return -1;
        lexer->pos++;
        if (handle_word(lexer) != 0)
            return -1;
        lexer->start = lexer->pos + 1;
        return 1;
    }
    return 0;
}
