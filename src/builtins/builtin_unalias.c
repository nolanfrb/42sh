/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** builtin_unalias
*/

#include <string.h>
#include <stdio.h>
#include "alias.h"

static int remove_alias(alias_t *alias, const char *name)
{
    int found = -1;

    for (int i = 0; i < alias->nb_alias; i++) {
        if (strcmp(alias->info[i]->name, name) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1)
        return 0;
    free(alias->info[found]->name);
    free(alias->info[found]->value);
    free(alias->info[found]);
    for (int i = found; i < alias->nb_alias - 1; i++) {
        alias->info[i] = alias->info[i + 1];
    }
    alias->nb_alias--;
    return 1;
}

static void parse_unalias_args(alias_t *alias, char **args)
{
    int count = count_args(args);

    if (count == 0) {
        fprintf(stderr, "unalias: Too few arguments.\n");
        return;
    }
    for (int i = 1; args[i]; i++) {
        remove_alias(alias, args[i]);
    }
}

int builtin_unalias(shell_t *shell, char **args)
{
    alias_t *alias = shell->alias;

    if (!alias)
        return 1;
    parse_unalias_args(alias, args);
    return 0;
}
