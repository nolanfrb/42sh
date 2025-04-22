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
 * @brief Handle a backslash escape sequence
 * @param i Current position pointer
 * @return 1 if escape was handled, 0 otherwise
 */
static int handle_backslash(int *i) 
{
    // Skip the current backslash and the next character
    (*i)++;
    return 1;
}

/**
 * @brief Handle quoted string (single or double quotes)
 * @param cmd_line Command line string
 * @param i Current position pointer
 * @param quote Type of quote (single or double)
 * @return 1 if quoted string was processed, 0 otherwise
 */
static int handle_quoted_string(char *cmd_line, int *i, char quote) 
{
    int start = *i;
    (*i)++; // Skip opening quote
    
    // Find closing quote
    while (cmd_line[*i] != '\0' && cmd_line[*i] != quote) {
        // Handle escaped characters in double quotes
        if (quote == QUOTE && cmd_line[*i] == BACKSLASH && 
            (cmd_line[*i + 1] == QUOTE || cmd_line[*i + 1] == BACKSLASH)) {
            (*i) += 2; // Skip both the backslash and the escaped character
        } else {
            (*i)++;
        }
    }
    
    if (cmd_line[*i] == quote) {
        (*i)++; // Skip closing quote
        return 1;
    }
    
    // Reset position if no closing quote
    *i = start; 
    return 0;
}

/**
 * @brief Check if position is inside an inhibitor section
 * @param cmd_line Command line string
 * @param pos Current position to check
 * @return true if inhibited, false otherwise
 */
bool is_inhibited_position(char *cmd_line, int pos)
{
    bool in_quotes = false;
    char quote_type = 0;
    bool escaped = false;
    
    for (int i = 0; i < pos; i++) {
        if (escaped) {
            escaped = false;
            continue;
        }
        if (cmd_line[i] == BACKSLASH && !in_quotes) {
            escaped = true;
            continue;
        }
        if (!in_quotes && (cmd_line[i] == QUOTE || cmd_line[i] == ANTI_QUOTE)) {
            in_quotes = true;
            quote_type = cmd_line[i];
            continue;
        }
        if (in_quotes && cmd_line[i] == quote_type) {
            in_quotes = false;
            quote_type = 0;
        }
    }
    return in_quotes || escaped;
}

/**
 * @brief Process inhibitors in command line
 * @param cmd_line Command line string
 * @param i Current position pointer
 * @param word_info Word info structure
 * @return 1 if inhibitor was processed, 0 otherwise, 84 on error
 */
int handle_inhibitors(char *cmd_line, int *i, word_info_t *word_info)
{
    if (cmd_line[*i] == BACKSLASH)
        return handle_backslash(i);
    if (cmd_line[*i] == QUOTE)
        return handle_quoted_string(cmd_line, i, QUOTE);
    if (cmd_line[*i] == ANTI_QUOTE)
        return handle_quoted_string(cmd_line, i, ANTI_QUOTE);
    return 0;
}
