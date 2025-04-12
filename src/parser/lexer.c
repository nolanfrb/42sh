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
#include "shell.h"
#include "ast.h"

const char *SPECIAL_TOKENS[] = {
    "(", ")", "&&", "||", ">>", "<<", ">", "<", "|", ";", "&", NULL
};

static bool is_delimiter(char c, char *delimiters)
{
    for (int i = 0; delimiters[i]; i++) {
        if (c == delimiters[i])
            return true;
    }
    return false;
}

static int check_special_token(const char *cmd_line, int pos)
{
    for (int i = 0; SPECIAL_TOKENS[i] != NULL; i++) {
        if (strncmp(cmd_line + pos, SPECIAL_TOKENS[i],
            strlen(SPECIAL_TOKENS[i])) == 0) {
            return i;
        }
    }
    return -1;
}

static int count_words(char *str, char *delimiters)
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

static char *extract_word(char *input, int start, int len)
{
    char *word = malloc(len + 1);

    if (word == NULL)
        exit(84);
    strncpy(word, input + start, len);
    word[len] = '\0';
    return word;
}

static void add_word_to_list(char *cmd_line, word_info_t *word_info, int *i)
{
    word_info->words[(word_info->word_idx)] = extract_word(cmd_line,
        word_info->start, *i - word_info->start);
    word_info->word_idx++;
    word_info->start = -1;
}

static void add_special_token_to_list(int token_idx, word_info_t *word_info,
    int *i)
{
    int token_len = strlen(SPECIAL_TOKENS[token_idx]);
    char *token = malloc(token_len + 1);

    if (token == NULL)
        exit(84);
    strncpy(token, SPECIAL_TOKENS[token_idx], token_len);
    token[token_len] = '\0';
    word_info->words[(word_info->word_idx)] = token;
    word_info->word_idx++;
    *i += token_len - 1;
}

static void handle_special_token(char *cmd_line, int *i,
    word_info_t *word_info)
{
    int token_idx = check_special_token(cmd_line, *i);

    if (token_idx == -1)
        return;
    if (word_info->start != -1)
        add_word_to_list(cmd_line, word_info, i);
    add_special_token_to_list(token_idx, word_info, i);
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
    char *delimiters)
{
    for (int i = 0; cmd_line[i] != '\0'; i++) {
        if (check_special_token(cmd_line, i) != -1) {
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

    word_info->words = malloc(sizeof(char *) *
        (count_words(cmd_line, delimiters) + 1));
    if (word_info->words == NULL)
        exit(84);
    word_info->word_idx = 0;
    word_info->start = -1;
    process_cmd_line(cmd_line, word_info, delimiters);
    if (word_info->start != -1) {
        word_info->words[word_info->word_idx] = extract_word(cmd_line,
            word_info->start, strlen(cmd_line) - word_info->start);
        word_info->word_idx++;
    }
    word_info->words[word_info->word_idx] = NULL;
    return word_info->words;
}
