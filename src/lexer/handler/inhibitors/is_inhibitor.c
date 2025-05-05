/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** is_inhibitor
*/

#include "inhibitors.h"
#include "lexer.h"

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
