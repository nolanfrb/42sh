/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** count_words
*/

#include <string.h>
#include "lexer.h"

int count_words(char *str, char *delimiters)
{
    int count = 0;
    int token_idx;
    bool in_word = false;

    for (int i = 0; str[i] != '\0'; i++) {
        token_idx = check_special_token(str, i);
        if (token_idx != -1) {
            count++;
            in_word = false;
            i += strlen(SPECIAL_TOKENS[token_idx]) - 1;
            continue;
        }
        if (is_delimiter(str[i], delimiters))
            in_word = false;
        if (!in_word && !is_delimiter(str[i], delimiters)) {
            in_word = true;
            count++;
        }
    }
    return count;
}
