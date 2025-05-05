/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** parse_alias_args
*/

#include "shell.h"
#include "alias.h"

int count_args(char **args)
{
    int count = 0;

    for (int i = 0; args[i]; i++)
        count++;
    return count;
}

int parse_alias_args(alias_t *alias, char **args)
{
    int count = count_args(args);

    if (count == 1)
        print_alias(alias, NULL, 0);
    if (count == 2)
        print_alias(alias, args[1], 1);
    if (count == 3)
        add_alias(alias, args[1], args[2]);
    return 0;
}
