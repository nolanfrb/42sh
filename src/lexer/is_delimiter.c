/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** is_delimiter
*/

#include <stdbool.h>

bool is_delimiter(char character, char *delimiters)
{
    for (int i = 0; delimiters[i]; i++) {
        if (character == delimiters[i])
            return true;
    }
    return false;
}
