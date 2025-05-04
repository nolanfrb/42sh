/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** extract_word
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "inhibitors.h"

char *extract_word(char *input, int start, int len)
{
    char *word = malloc(len + 1);

    if (!word)
        return NULL;
    strncpy(word, input + start, len);
    word[len] = '\0';
    return word;
}

char *extract_inhibited_content(char *cmd_line, int start, int end)
{
    int length = end - start - 1;
    char *content = malloc(sizeof(char) * (length + 1));

    if (!content)
        return NULL;
    strncpy(content, &cmd_line[start + 1], length);
    content[length] = '\0';
    return content;
}
