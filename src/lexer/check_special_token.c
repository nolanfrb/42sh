/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** check_special_token
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"

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
