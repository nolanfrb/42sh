/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** extract_word
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"

char *extract_word(char *input, int start, int len)
{
    char *word = malloc(len + 1);

    if (!word)
        return NULL;
    strncpy(word, input + start, len);
    word[len] = '\0';
    return word;
}
