/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** handle_braced_variables
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int is_variable_char(char c)
{
    return isalnum(c) || c == '_';
}

static char *get_var_name(char *input, int start, int len)
{
    char *var_name = malloc(len + 1);

    if (!var_name)
        return NULL;
    strncpy(var_name, input + start, len);
    var_name[len] = '\0';
    return var_name;
}

static char *extract_braced_variable(char *input, int start, int *end)
{
    int i = start;
    int len = 0;

    i++;
    if (input[i] == '{') {
        i++;
        start = i;
        while (input[i] != '\0' && input[i] != '}')
            i++;
        if (input[i] == '}') {
            *end = i;
            len = i - start;
            return get_var_name(input, start, len);
        }
        fprintf(stderr, "Missing '}'.\n");
        return NULL;
    }
    return NULL;
}

static char *extract_simple_variable(char *input, int start, int *end)
{
    int i = start;
    int len;

    i++;
    start = i;
    while (input[i] != '\0' && is_variable_char(input[i]))
        i++;
    *end = i - 1;
    len = i - start;
    return get_var_name(input, start, len);
}

char *extract_variable_name(char *input, int start, int *end)
{
    if (input[start + 1] == '{')
        return extract_braced_variable(input, start, end);
    else
        return extract_simple_variable(input, start, end);
}
