/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** inhibitors
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "inhibitors.h"
#include <stdio.h>
#include "utils.h"

static void update_inhibitor_state(lexer_t *lexer, char c)
{
    if (lexer->inhibitor_state == STATE_NORMAL) {
        if (c == '"')
            lexer->inhibitor_state = STATE_DOUBLE_QUOTE;
        else if (c == '\'')
            lexer->inhibitor_state = STATE_SINGLE_QUOTE;
    } else if (lexer->inhibitor_state == STATE_DOUBLE_QUOTE && c == '"') {
        lexer->inhibitor_state = STATE_NORMAL;
    } else if (lexer->inhibitor_state == STATE_SINGLE_QUOTE && c == '\'') {
        lexer->inhibitor_state = STATE_NORMAL;
    }
}

static int handle_quote_start(lexer_t *lexer, char c)
{
    if (lexer->start != lexer->pos && handle_word(lexer) != 0)
        return -1;
    update_inhibitor_state(lexer, c);
    lexer->pos++;
    lexer->start = lexer->pos;
    return 0;
}

static int handle_quote_end(lexer_t *lexer, char c)
{
    if (lexer->start != lexer->pos && handle_word(lexer) != 0)
        return -1;
    update_inhibitor_state(lexer, c);
    lexer->pos++;
    lexer->start = lexer->pos;
    return 0;
}

static int handle_backslash(lexer_t *lexer)
{
    if (lexer->input[lexer->pos + 1] == '\0')
        return 0;
    lexer->pos += 2;
    return 0;
}

int handle_inhibitor(lexer_t *lexer, char c)
{
    if (c == BACKSLASH)
        return handle_backslash(lexer);
    if (c == DOUBLE_QUOTE) {
        if (lexer->inhibitor_state == STATE_NORMAL)
            return handle_quote_start(lexer, c);
        else if (lexer->inhibitor_state == STATE_DOUBLE_QUOTE)
            return handle_quote_end(lexer, c);
    }
    if (c == SIMPLE_QUOTE) {
        if (lexer->inhibitor_state == STATE_NORMAL)
            return handle_quote_start(lexer, c);
        else if (lexer->inhibitor_state == STATE_SINGLE_QUOTE)
            return handle_quote_end(lexer, c);
    }
    return 0;
}
