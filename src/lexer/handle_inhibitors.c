/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_inhibitors
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "shell.h"
#include "inhibitors.h"
#include "utils.h"

static bool is_escaped(const char *cmd_line, int pos)
{
    int backslash_count = 0;

    pos--;
    while (pos >= 0 && cmd_line[pos] == BACKSLASH) {
        backslash_count++;
        pos--;
    }
    return (backslash_count % 2) == 1;
}

int find_inhibitor_end(char *cmd_line, int start, char inhibitor)
{
    int i = start + 1;

    while (cmd_line[i] != '\0') {
        if (inhibitor == BACKSLASH)
            return i + 1;
        if (cmd_line[i] == inhibitor && !is_escaped(cmd_line, i))
            return i;
        if (inhibitor == DOUBLE_QUOTE && cmd_line[i] == BACKSLASH &&
            cmd_line[i + 1] != '\0')
            i++;
        i++;
    }
    return -1;
}

static int handle_inhibitor_error(char inhibitor, char *content)
{
    fprintf(stderr, "Unmatched \"%c\"\n", inhibitor);
    free(content);
    return -1;
}

int process_inhibitor(char *cmd_line, int *pos, char **combined)
{
    char current_inhibitor = cmd_line[*pos];
    int end = find_inhibitor_end(cmd_line, *pos, current_inhibitor);
    char *content = NULL;

    if (end == -1)
        return handle_inhibitor_error(current_inhibitor, *combined);
    content = extract_inhibited_content(cmd_line, *pos, end);
    if (!content) {
        free(*combined);
        return -1;
    }
    *combined = safe_strcat(*combined, content);
    if (!*combined)
        return -1;
    *pos = end;
    return 0;
}

char *process_inhibitor_sequence(char *cmd_line, int *pos)
{
    char *combined = NULL;
    int result;

    while (cmd_line[*pos] != '\0') {
        result = process_inhibitor(cmd_line, pos, &combined);
        if (result == -1)
            return NULL;
        if (is_inhibitor(cmd_line[*pos + 1]))
            (*pos)++;
        else
            break;
    }
    return combined;
}

int process_inhibited_zone(
    char *cmd_line, inhibitor_t *inhibitor, word_info_t *word_info
)
{
    char *content;
    int pos = *inhibitor->start;

    content = process_inhibitor_sequence(cmd_line, &pos);
    if (!content)
        return 84;
    word_info->words[word_info->word_idx] = content;
    word_info->word_idx++;
    *inhibitor->start = pos;
    return 0;
}

bool is_inhibitor(char c)
{
    switch (c) {
        case BACKSLASH:
            return true;
        case DOUBLE_QUOTE:
            return true;
        case SIMPLE_QUOTE:
            return true;
        case BACKTICK:
            return true;
    }
    return false;
}
