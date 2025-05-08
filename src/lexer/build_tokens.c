/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** build_tokens
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"

char **build_tokens(const char *input, shell_t *shell)
{
    lexer_t *lexer_struct = NULL;
    char **tokens = NULL;

    if (!input || !shell)
        return NULL;
    lexer_struct = lexer_create(input, shell);
    if (!lexer_struct)
        return NULL;
    tokens = lexer_to_strings(lexer_struct);
    if (!tokens) {
        lexer_destroy(lexer_struct);
        return NULL;
    }
    lexer_destroy(lexer_struct);
    return tokens;
}
