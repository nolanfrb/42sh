/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** lexer
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include <stdio.h>

int lexer_tokenize(lexer_t *lexer)
{
    char *input = lexer->input;

    for (int i = 0; input[i] != '\0'; i++)
        printf("Current letter = [%c]\n", input[i]);
    return 0;
}

lexer_t *lexer_build(const char *input)
{
    lexer_t *lexer = lexer_init(input);
    if (!lexer)
        return NULL;
    lexer_tokenize(lexer);
    return lexer;
}
