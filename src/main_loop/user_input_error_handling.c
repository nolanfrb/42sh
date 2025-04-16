/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** user_input_error_handling
*/

#include <stdio.h>
#include "shell.h"

static int check_parentheses(char **tokens)
{
    int open_parentheses = 0;
    int close_parentheses = 0;

    for (int i = 0; tokens[i] != NULL; i++) {
        if (tokens[i][0] == '(')
            open_parentheses++;
        if (tokens[i][0] == ')')
            close_parentheses++;
    }
    if (open_parentheses > close_parentheses) {
        fprintf(stderr, "Too many ('s.\n");
        return -1;
    }
    if (open_parentheses < close_parentheses) {
        fprintf(stderr, "Too many )'s.\n");
        return -1;
    }
    return 0;
}

int user_input_error_handling(char **tokens)
{
    if (!tokens) {
        fprintf(stderr, "Error: user_input is NULL\n");
        return 84;
    }
    if (check_parentheses(tokens) == -1)
        return 84;
    return 0;
}