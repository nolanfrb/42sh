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
#include "lexer.h"
#include "inhibitors.h"

static int process_special_token(char *cmd_line, int *i,
    word_info_t *word_info)
{
    if (check_special_token(cmd_line, *i) != -1) {
        if (handle_special_token(cmd_line, i, word_info) != 0)
            return 84;
        return 1;
    }
    return 0;
}

static int process_cmd_line(char *cmd_line, word_info_t *word_info,
    char *delimiters)
{
    int special_token_result;

    for (int i = 0; cmd_line[i] != '\0'; i++) {
        if (is_inhibited_delimiter(cmd_line, i))
            continue;
        special_token_result = process_special_token(cmd_line, &i, word_info);
        if (special_token_result == 84)
            return 84;
        if (special_token_result == 1)
            continue;
        if (handle_delimiter(cmd_line, &i, word_info, delimiters) != 0)
            return 84;
    }
    return 0;
}

static word_info_t *init_word_info(char *cmd_line, char *delimiters)
{
    word_info_t *word_info = malloc(sizeof(word_info_t));

    if (!word_info)
        return NULL;
    word_info->words = malloc(sizeof(char *) *
        (count_words(cmd_line, delimiters) + 1));
    if (!word_info->words) {
        free(word_info);
        return NULL;
    }
    word_info->word_idx = 0;
    word_info->start = -1;
    return word_info;
}

char **lexer(char *cmd_line)
{
    char *delimiters = " \t\n";
    word_info_t *word_info = init_word_info(cmd_line, delimiters);

    if (!word_info)
        return NULL;
    if (process_cmd_line(cmd_line, word_info, delimiters) != 0)
        return NULL;
    if (word_info->start != -1) {
        word_info->words[word_info->word_idx] = extract_word(cmd_line,
            word_info->start, strlen(cmd_line) - word_info->start);
        if (word_info->words[word_info->word_idx] == NULL)
            return NULL;
        word_info->word_idx++;
    }
    word_info->words[word_info->word_idx] = NULL;
    return word_info->words;
}
