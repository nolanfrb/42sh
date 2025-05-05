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

static int handle_word(lexer_t *lexer)
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

static int handle_pipe(lexer_t *lexer)
{
    if (lexer->input[lexer->pos + 1] == '|') {
        lexer->pos++;
        return lexer_add_token(lexer, TOKEN_OR, "||");
    }
    return lexer_add_token(lexer, TOKEN_PIPE, "|");
}

static int handle_and(lexer_t *lexer)
{
    if (lexer->input[lexer->pos + 1] == '&') {
        lexer->pos++;
        return lexer_add_token(lexer, TOKEN_AND, "&&");
    }
    lexer->pos++;
    return handle_word(lexer);
}

static int handle_redirect_in(lexer_t *lexer)
{
    if (lexer->input[lexer->pos + 1] == '<') {
        lexer->pos++;
        return lexer_add_token(lexer, TOKEN_HEREDOC, "<<");
    }
    return lexer_add_token(lexer, TOKEN_REDIRECT_IN, "<");
}

static int handle_redirect_out(lexer_t *lexer)
{
    if (lexer->input[lexer->pos + 1] == '>') {
        lexer->pos++;
        return lexer_add_token(lexer, TOKEN_APPEND_OUT, ">>");
    }
    return lexer_add_token(lexer, TOKEN_REDIRECT_OUT, ">");
}

static int handle_special_char(lexer_t *lexer)
{
    char c = lexer->input[lexer->pos];

    if (lexer->start != lexer->pos && handle_word(lexer) != 0)
        return -1;
    lexer->start = lexer->pos;
    switch (c) {
        case '|':
            return handle_pipe(lexer);
        case '&':
            return handle_and(lexer);
        case ';':
            return lexer_add_token(lexer, TOKEN_SEMICOLON, ";");
        case '<':
            return handle_redirect_in(lexer);
        case '>':
            return handle_redirect_out(lexer);
        default:
            break;
    }
    return 0;
}

static int process_char(lexer_t *lexer)
{
    char c = lexer->input[lexer->pos];

    if (is_special_char(&c)) {
        if (handle_special_char(lexer) != 0)
            return -1;
        lexer->start = lexer->pos + 1;
    } else if (is_whitespace(c)) {
        if (lexer->start != lexer->pos && handle_word(lexer) != 0)
            return -1;
        lexer->start = lexer->pos + 1;
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
        lexer->pos++;
    }
    if (lexer->start != lexer->pos && handle_word(lexer) != 0)
        return -1;
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
