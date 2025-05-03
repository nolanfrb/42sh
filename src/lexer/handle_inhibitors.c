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

static int find_inhibitor_end(char *cmd_line, int start, char inhibitor)
{
    int i = start + 1;
    
    while (cmd_line[i] != '\0') {
        if (inhibitor == '\\') {
            return i + 1;
        } else if (cmd_line[i] == inhibitor) {
            return i;
        }
        if (inhibitor == DOUBLE_QUOTE && cmd_line[i] == BACKSLASH && cmd_line[i + 1] != '\0')
            i++;
        i++;
    }
    return -1;
}

static char *extract_inhibited_content(char *cmd_line, int start, int end)
{
    int length = end - start - 1;
    char *content = malloc(sizeof(char) * (length + 1));
    
    if (!content)
        return NULL;
    strncpy(content, &cmd_line[start + 1], length);
    content[length] = '\0';
    return content;
}

int process_inhibited_zone(char *cmd_line, inhibitor_t *inhibitor, word_info_t *word_info)
{
    int end = 0;
    char *content = NULL;

    inhibitor->character = cmd_line[*inhibitor->start];
    end = find_inhibitor_end(cmd_line, *inhibitor->start, inhibitor->character);
    if (end == -1) {
        fprintf(stderr, "Unmatched \"%c\"\n", inhibitor->character);
        return 84;
    }
    if (inhibitor->character == BACKSLASH) {
        *inhibitor->start = end;
        return 0;
    }
    if (is_inhibitor(cmd_line[end + 1], inhibitor)) {
        *inhibitor->start = end + 1;
        process_inhibited_zone(cmd_line, inhibitor, word_info);
        return 0;
    }
    content = extract_inhibited_content(cmd_line, *inhibitor->start, end);
    if (!content)
        return 84;
    word_info->words[word_info->word_idx++] = content;
    *inhibitor->start = end;
    return 0;
}

bool is_inhibitor(char c, inhibitor_t *inhibitor)
{

    switch (c) {
        case BACKSLASH:
            inhibitor->character = BACKSLASH;
            return true;
        case DOUBLE_QUOTE:
            inhibitor->character = DOUBLE_QUOTE;
            return true;
        case SIMPLE_QUOTE:
            inhibitor->character = SIMPLE_QUOTE;
            return true;
        case BACKTICK:
            inhibitor->character = BACKTICK;
            return true;
    }
    return false;
}