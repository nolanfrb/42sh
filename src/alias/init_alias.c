/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** init_alias
*/

#include <stdlib.h>
#include <stdio.h>
#include "alias.h"

alias_t *init_alias(int count)
{
    alias_t *alias = malloc(sizeof(alias_t));

    if (!alias)
        return NULL;
    alias->nb_alias = count;
    alias->info = malloc(sizeof(alias_info_t *) * (count + 1));
    if (!alias->info) {
        perror("malloc");
        return NULL;
    }
    for (int i = 0; i <= count; i++) {
        alias->info[i] = malloc(sizeof(alias_info_t));
        if (!alias->info[i]) {
            perror("malloc");
            return NULL;
        }
        alias->info[i]->name = NULL;
        alias->info[i]->value = NULL;
    }
    return alias;
}
