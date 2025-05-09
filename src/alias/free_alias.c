/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** free_alias
*/

#include <stdlib.h>
#include "alias.h"

void free_alias(alias_t *alias)
{
    if (!alias)
        return;
    for (int i = 0; i < alias->nb_alias; i++) {
        if (alias->info[i]->name)
            free(alias->info[i]->name);
        if (alias->info[i]->value)
            free(alias->info[i]->value);
        if (alias->info[i])
            free(alias->info[i]);
    }
    free(alias);
}
