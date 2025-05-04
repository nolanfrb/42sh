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
