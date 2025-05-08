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

bool is_special_char(char *str)
{
    for (int i = 0; SPECIAL_TOKENS[i] != NULL; i++) {
        if (strncmp(str, SPECIAL_TOKENS[i],
            strlen(SPECIAL_TOKENS[i])) == 0) {
            return true;
        }
    }
    return false;
}
