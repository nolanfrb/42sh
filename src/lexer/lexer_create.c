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
#include "inhibitors.h"

int handle_word(lexer_t *lexer)
{
    int len = lexer->pos - lexer->start;
    char *word = malloc(sizeof(char) * (len + 1));

    if (!word)
        return -1;
    strncpy(word, lexer->input + lexer->start, len);
    word[len] = '\0';
    if (lexer_add_token(lexer, TOKEN_WORD, word) != 0) {
        free(word);
        return -1;
    }
    free(word);
    return 0;
}

int handle_special_char(lexer_t *lexer)
{
    char c = lexer->input[lexer->pos];
    const special_char_handler_t *handler = get_special_chars();

    if (lexer->start != lexer->pos && handle_word(lexer) != 0)
        return -1;
    lexer->start = lexer->pos;
    while (handler->symbol != '\0') {
        if (handler->symbol == c)
            return handler->handler(lexer);
        handler++;
    }
    return 0;
}

int lexer_tokenize(lexer_t *lexer)
{
    lexer->pos = 0;
    lexer->start = 0;
    while (lexer->input[lexer->pos] != '\0') {
        if (process_char(lexer) != 0)
            return -1;
    }
    if (lexer->start != lexer->pos && handle_word(lexer) != 0)
        return -1;
    return 0;
}

lexer_t *lexer_create(const char *input, shell_t *shell)
{
    lexer_t *lexer = lexer_init(input, shell);

    if (!lexer)
        return NULL;
    lexer_tokenize(lexer);
    return lexer;
}
