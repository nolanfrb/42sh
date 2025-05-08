/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** process_character
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "inhibitors.h"
#include "utils.h"

static int process_inhibitors(lexer_t *lexer)
{
    char c = lexer->input[lexer->pos];
    int inhibitor_result = 0;

    if (is_inhibitor(c)) {
        inhibitor_result = handle_inhibitor(lexer, c);
        if (inhibitor_result != 0)
            return inhibitor_result;
        return 1;
    }
    return 0;
}

static int process_variables(lexer_t *lexer)
{
    char c = lexer->input[lexer->pos];
    int var_result = 0;

    if (c == '$' && lexer->state != LEXER_INHIBITOR) {
        var_result = handle_variable(lexer, lexer->shell);
        if (var_result != 0)
            return var_result < 0 ? -1 : 1;
    }
    return 0;
}

static int process_special_chars(lexer_t *lexer)
{
    char c = lexer->input[lexer->pos];

    if (is_special_char(&c) && lexer->inhibitor_state == STATE_NORMAL) {
        if (handle_special_char(lexer) != 0)
            return -1;
        lexer->start = lexer->pos;
        return 1;
    }
    return 0;
}

static int process_whitespace(lexer_t *lexer)
{
    char c = lexer->input[lexer->pos];

    if (is_whitespace(c) && lexer->inhibitor_state == STATE_NORMAL) {
        if (lexer->start != lexer->pos && handle_word(lexer) != 0)
            return -1;
        lexer->start = lexer->pos + 1;
    }
    return 0;
}

int process_char(lexer_t *lexer)
{
    int result = 0;

    result = process_inhibitors(lexer);
    if (result != 0)
        return result < 0 ? -1 : 0;
    result = process_variables(lexer);
    if (result != 0)
        return result < 0 ? -1 : 0;
    result = process_special_chars(lexer);
    if (result != 0)
        return result < 0 ? -1 : 0;
    result = process_whitespace(lexer);
    if (result != 0)
        return result < 0 ? -1 : 0;
    lexer->pos++;
    return 0;
}
