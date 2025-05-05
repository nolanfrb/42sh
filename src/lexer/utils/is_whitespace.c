/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_whitespace
*/

#include "lexer.h"

bool is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}
