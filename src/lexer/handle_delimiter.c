/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** handle_delimiter
*/

#include <stdlib.h>
#include "lexer.h"

static int finalize_current_word(char *cmd_line, int i, word_info_t *word_info)
{
    if (word_info->start != -1) {
        word_info->words[(word_info->word_idx)] = extract_word(cmd_line,
            word_info->start, i - word_info->start);
        if (word_info->words[(word_info->word_idx)] == NULL)
            return 84;
        word_info->word_idx++;
        word_info->start = -1;
    }
    return 0;
}

int handle_delimiter(char *cmd_line, int *i, word_info_t *word_info,
    char *delimiters)
{
    if (is_delimiter(cmd_line[*i], delimiters)) {
        return finalize_current_word(cmd_line, *i, word_info);
    } else if (word_info->start == -1) {
        word_info->start = *i;
    }
    return 0;
}
