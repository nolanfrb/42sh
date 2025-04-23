/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_inhibitors
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "shell.h"
#include "inhibitors.h"

bool is_inhibited_delimiter(const char *line, int pos)
{
    bool in_single = false;
    bool in_double = false;
    bool escaped = false;

    for (int i = 0; i < pos; i++) {
        if (escaped) {
            escaped = false;
            continue;
        }
        if (line[i] == '\\' && !in_single) {
            escaped = true;
            continue;
        }
        if (line[i] == '"' && !in_single) {
            in_double = !in_double;
            continue;
        }
        if (line[i] == '\'' && !in_double)
            in_single = !in_single;
    }
    return in_single || in_double || escaped;
}
