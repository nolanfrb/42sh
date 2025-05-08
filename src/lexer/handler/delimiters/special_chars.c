/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** special_chars
*/

#include "lexer.h"
#include <stdlib.h>

const special_char_handler_t *get_special_chars(void)
{
    static const special_char_handler_t special_chars[] = {
        {'(', handle_left_parenthesis},
        {')', handle_right_parenthesis},
        {'|', handle_pipe},
        {'&', handle_and},
        {'<', handle_redirect_in},
        {'>', handle_redirect_out},
        {';', handle_semicolon},
        {'\0', NULL}
    };

    return special_chars;
}
