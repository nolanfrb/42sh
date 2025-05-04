/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** process_line
*/

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** process_cmd_line
*/

#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "shell.h"
#include "inhibitors.h"
#include "utils.h"
#include "ast.h"

static int handle_backslash(char *cmd_line, int *i)
{
    if (cmd_line[*i] == BACKSLASH && cmd_line[*i + 1] != '\0') {
        (*i)++;
        return 1;
    }
    return 0;
}

static int handle_inhibitors(
    char *cmd_line, int *i, inhibitor_t *inhibitor, word_info_t *word_info)
{
    inhibitor->start = i;
    if (is_inhibitor(cmd_line[*i])) {
        if (process_inhibited_zone(cmd_line, inhibitor, word_info) != 0)
            return 84;
        return 1;
    }
    return 0;
}

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

static int process_character(
    char *cmd_line, int *i, word_info_t *word_info, char *delimiters
)
{
    int special_token_result = 0;

    special_token_result = process_special_token(cmd_line, i, word_info);
    if (special_token_result == 84)
        return 84;
    if (special_token_result == 1)
        return 1;
    if (handle_delimiter(cmd_line, i, word_info, delimiters) != 0)
        return 84;
    return 0;
}

int process_cmd_line(char *cmd_line, word_info_t *word_info,
    char *delimiters)
{
    inhibitor_t inhibitor = {0};
    int result;

    for (int i = 0; cmd_line[i] != '\0'; i++) {
        if (handle_backslash(cmd_line, &i) &&
            check_special_token(cmd_line, i) != -1)
            continue;
        result = handle_inhibitors(cmd_line, &i, &inhibitor, word_info);
        if (result == 84)
            return 84;
        if (result == 1)
            continue;
        result = process_character(cmd_line, &i, word_info, delimiters);
        if (result == 84)
            return 84;
        if (result == 1)
            continue;
    }
    return 0;
}
