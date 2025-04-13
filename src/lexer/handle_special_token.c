/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** handle_special_token
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static int add_word_to_list(char *cmd_line, word_info_t *word_info, int *i)
{
    word_info->words[(word_info->word_idx)] = extract_word(cmd_line,
        word_info->start, *i - word_info->start);
    if (word_info->words[(word_info->word_idx)] == NULL)
        return 84;
    word_info->word_idx++;
    word_info->start = -1;
    return 0;
}

static int add_special_token_to_list(int token_idx, word_info_t *word_info,
    int *i)
{
    int token_len = strlen(SPECIAL_TOKENS[token_idx]);
    char *token = malloc(token_len + 1);

    if (!token)
        return 84;
    strncpy(token, SPECIAL_TOKENS[token_idx], token_len);
    token[token_len] = '\0';
    word_info->words[(word_info->word_idx)] = token;
    word_info->word_idx++;
    *i += token_len - 1;
    return 0;
}

int handle_special_token(char *cmd_line, int *i,
    word_info_t *word_info)
{
    int token_idx = check_special_token(cmd_line, *i);

    if (token_idx == -1)
        return;
    if (word_info->start != -1 &&
        add_word_to_list(cmd_line, word_info, i) != 0)
        return 84;
    if (add_special_token_to_list(token_idx, word_info, i) != 0)
        return 84;
    return 0;
}
