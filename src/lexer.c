/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** lexer
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "ast.h"


static bool is_delimiter(char c, char *delimiters)
{
    for (int i = 0; delimiters[i]; i++) {
        if (c == delimiters[i])
            return true;
    }
    return false;
}

static int count_words(char *str, char *delimiters)
{
    int count = 0;
    bool in_word = false;
    char *special_tokens = ";|&<>";

    for (int i = 0; str[i] != '\0'; i++) {
        if (strchr(special_tokens, str[i]) != NULL) {
            count++;
            in_word = false;
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

static char *extract_word(char *input, int start, int len)
{
    char *word = malloc(len + 1);

    if (word == NULL)
        exit(84);
    strncpy(word, input + start, len);
    word[len] = '\0';
    return word;
}

static void handle_special_token(char *cmd_line, int *i, word_info_t
    *word_info)
{
    char *token;

    if (word_info->start != -1) {
        word_info->words[(word_info->word_idx)] = extract_word(cmd_line,
            word_info->start, *i - word_info->start);
        word_info->word_idx++;
        word_info->start = -1;
    }
    token = malloc(2);
    if (token == NULL)
        exit(84);
    token[0] = cmd_line[*i];
    token[1] = '\0';
    word_info->words[(word_info->word_idx)] = token;
    word_info->word_idx++;
}

static void handle_delimiter(char *cmd_line, int *i, word_info_t *word_info,
    char *delimiters)
{
    if (is_delimiter(cmd_line[*i], delimiters)) {
        if (word_info->start != -1) {
            word_info->words[(word_info->word_idx)] = extract_word(cmd_line,
                word_info->start, *i - word_info->start);
            word_info->word_idx++;
            word_info->start = -1;
        }
    } else if (word_info->start == -1) {
        word_info->start = *i;
    }
}

static void process_cmd_line(char *cmd_line, word_info_t *word_info,
    char *delimiters, char *special_tokens)
{
    for (int i = 0; cmd_line[i] != '\0'; i++) {
        if (strchr(special_tokens, cmd_line[i]) != NULL) {
            handle_special_token(cmd_line, &i, word_info);
            continue;
        }
        handle_delimiter(cmd_line, &i, word_info, delimiters);
    }
}

char **lexer(char *cmd_line)
{
    word_info_t *word_info = malloc(sizeof(word_info_t));
    char *delimiters = " \t\n";
    char *special_tokens = ";|&<>";

    word_info->words = malloc(sizeof(char *) *
    (count_words(cmd_line, delimiters) + 1));
    word_info->word_idx = 0;
    word_info->start = -1;
    if (word_info->words == NULL)
        exit(84);
    process_cmd_line(cmd_line, word_info, delimiters, special_tokens);
    if (word_info->start != -1)
        word_info->words[word_info->word_idx] = extract_word(cmd_line,
            word_info->start, strlen(cmd_line) - word_info->start);
        word_info->word_idx++;
    word_info->words[word_info->word_idx] = NULL;
    return word_info->words;
}
