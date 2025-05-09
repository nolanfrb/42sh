/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** process_variables
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "utils.h"

static int check_continue_concat(lexer_t *lexer, int end, char *result)
{
    if (lexer->input[end + 1] == '$') {
        lexer->pos = end + 1;
        lexer->state = LEXER_VARIABLE;
        lexer->concat_buffer = strdup(result);
        return 1;
    }
    return 0;
}

static int finalize_variable_token(lexer_t *lexer, char *result, int end)
{
    int continue_concat = check_continue_concat(lexer, end, result);

    if (continue_concat)
        return 1;
    if (lexer_add_token(lexer, TOKEN_VARIABLE, result) != 0) {
        free(result);
        return -1;
    }
    free(result);
    lexer->pos = end + 1;
    lexer->start = lexer->pos;
    return 1;
}

static char *process_with_concat_buffer(lexer_t *lexer, char *var_value)
{
    char *result = safe_strcat(lexer->concat_buffer, var_value);

    if (!result)
        return NULL;
    lexer->concat_buffer = NULL;
    return result;
}

static char *process_with_word_part(lexer_t *lexer, char *var_value)
{
    char *word_part = get_current_word_part(lexer);

    if (!word_part) {
        free(var_value);
        return NULL;
    }
    return safe_strcat(word_part, var_value);
}

int process_variable_value(
    lexer_t *lexer, char *var_value, int end, int is_concat
)
{
    char *result = NULL;

    if (!var_value)
        return -1;
    if (lexer->state == LEXER_VARIABLE && lexer->concat_buffer)
        result = process_with_concat_buffer(lexer, var_value);
    else if (is_concat)
        result = process_with_word_part(lexer, var_value);
    else
        result = var_value;
    if (!result)
        return -1;
    return finalize_variable_token(lexer, result, end);
}
