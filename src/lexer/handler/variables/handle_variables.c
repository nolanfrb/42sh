/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_variable
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "shell.h"
#include "env.h"
#include <stdio.h>
#include "utils.h"

static char *get_variable_value(shell_t *shell, char *var_name)
{
    char *value = NULL;

    value = get_local_value(shell, var_name);
    if (value)
        return strdup(value);
    value = get_env_value(shell, var_name);
    if (value)
        return strdup(value);
    fprintf(stderr, "%s: Undefined variable.\n", var_name);
    return NULL;
}

static char *get_current_word_part(lexer_t *lexer)
{
    int len = lexer->pos - lexer->start;
    char *word_part = NULL;

    if (len <= 0)
        return strdup("");
    word_part = malloc(sizeof(char) * (len + 1));
    if (!word_part)
        return NULL;
    strncpy(word_part, lexer->input + lexer->start, len);
    word_part[len] = '\0';
    return word_part;
}

static int process_variable_value(lexer_t *lexer, char *var_value, int end,
                                  int is_concat)
{
    char *word_part = NULL;
    char *result = NULL;

    if (!var_value)
        return -1;
    if (is_concat) {
        word_part = get_current_word_part(lexer);
        if (!word_part) {
            free(var_value);
            return -1;
        }
        result = safe_strcat(word_part, var_value);
        if (!result)
            return -1;
        if (lexer_add_token(lexer, TOKEN_WORD, result) != 0) {
            free(result);
            return -1;
        }
        free(result);
    } else if (lexer_add_token(lexer, TOKEN_WORD, var_value) != 0) {
        free(var_value);
        return -1;
    }
    lexer->pos = end + 1;
    lexer->start = lexer->pos;
    return 1;
}

int handle_variable(lexer_t *lexer, shell_t *shell)
{
    char *var_name = NULL;
    char *var_value = NULL;
    int end = 0;
    int is_concat = 0;

    if (lexer->input[lexer->pos] != '$')
        return 0;
    is_concat = (lexer->start != lexer->pos);
    var_name = extract_variable_name(lexer->input, lexer->pos, &end);
    if (!var_name)
        return -1;
    var_value = get_variable_value(shell, var_name);
    free(var_name);
    return process_variable_value(lexer, var_value, end, is_concat);
}
