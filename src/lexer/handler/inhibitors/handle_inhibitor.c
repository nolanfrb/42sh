/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** inhibitors
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "inhibitors.h"
#include "utils.h"

static int handle_quote_boundary(lexer_t *lexer)
{
    if (lexer->start != lexer->pos) {
        if (handle_word(lexer) != 0) {
            return -1;
        }
    }
    if (lexer->inhibitor_state != STATE_NORMAL) {
        lexer->state = LEXER_INHIBITOR;
    }
    lexer->pos++;
    lexer->start = lexer->pos;
    return 0;
}

static int handle_double_quote(lexer_t *lexer)
{
    if (lexer->inhibitor_state == STATE_NORMAL) {
        if (strchr(lexer->input + lexer->pos + 1, DOUBLE_QUOTE) == NULL) {
            fprintf(stderr, "Unmatched \"%c\".\n", DOUBLE_QUOTE);
            return -1;
        }
        lexer->inhibitor_state = STATE_DOUBLE_QUOTE;
    } else if (lexer->inhibitor_state == STATE_DOUBLE_QUOTE) {
        lexer->inhibitor_state = STATE_NORMAL;
    }
    return handle_quote_boundary(lexer);
}

static int handle_single_quote(lexer_t *lexer)
{
    if (lexer->inhibitor_state == STATE_NORMAL) {
        if (strchr(lexer->input + lexer->pos + 1, SIMPLE_QUOTE) == NULL) {
            fprintf(stderr, "Unmatched '%c'.\n", SIMPLE_QUOTE);
            return -1;
        }
        lexer->inhibitor_state = STATE_SINGLE_QUOTE;
    } else if (lexer->inhibitor_state == STATE_SINGLE_QUOTE) {
        lexer->inhibitor_state = STATE_NORMAL;
    }
    return handle_quote_boundary(lexer);
}

static int handle_backslash(lexer_t *lexer)
{
    if (lexer->input[lexer->pos + 1] == '\0') {
        fprintf(stderr, "Unmatched '%c'.\n", BACKSLASH);
        return -1;
    }
    lexer->pos += 2;
    return 0;
}

int handle_inhibitor(lexer_t *lexer, char c)
{
    switch (c) {
        case BACKSLASH:
            return handle_backslash(lexer);
        case DOUBLE_QUOTE:
            return handle_double_quote(lexer);
        case SIMPLE_QUOTE:
            return handle_single_quote(lexer);
        default:
            return 0;
    }
}
