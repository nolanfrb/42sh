/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_delimiter
*/

#include "lexer.h"
#include <stdlib.h>
#include <string.h>

const char *SPECIAL_TOKENS[] = {
    "(", ")", "&&", "||", ">>", "<<", ">", "<", "|", ";", "&", NULL
};

int check_special_token(const char *cmd_line, int pos)
{
    for (int i = 0; SPECIAL_TOKENS[i] != NULL; i++) {
        if (strncmp(cmd_line + pos, SPECIAL_TOKENS[i],
            strlen(SPECIAL_TOKENS[i])) == 0) {
            return i;
        }
    }
    return -1;
}
