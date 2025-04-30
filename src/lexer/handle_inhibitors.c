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

/**
 * @brief Update quote states based on current character
 * @param c Current character
 * @param in_single Pointer to single quote state
 * @param in_double Pointer to double quote state
 * @param escaped Pointer to escaped state
 */
static void update_quote_state(char c, bool *in_single, bool *in_double,
    bool *escaped)
{
    if (*escaped) {
        *escaped = false;
        return;
    }
    if (c == '\\' && !*in_single) {
        *escaped = true;
        return;
    }
    if (c == '"' && !*in_single)
        *in_double = !*in_double;
    else if (c == '\'' && !*in_double)
        *in_single = !*in_single;
}

/**
 * @brief Check if character at position is within quotes or escaped
 * @param line Input string to check
 * @param pos Position to check
 * @return true if position is within quotes or escaped
 */
bool is_inhibited_delimiter(const char *line, int pos)
{
    bool in_single = false;
    bool in_double = false;
    bool escaped = false;

    for (int i = 0; i < pos; i++)
        update_quote_state(line[i], &in_single, &in_double, &escaped);
    return in_single || in_double || escaped;
}
