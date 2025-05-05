/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** print_alias
*/

#include <string.h>
#include "shell.h"
#include "alias.h"

void print_alias(alias_t *alias, char *name, bool specific)
{
    if (!specific) {
        for (int i = 0; i < alias->nb_alias; i++) {
            printf_flush("%s\t%s\n", alias->info[i]->name,
                alias->info[i]->value);
        }
        return;
    }
    for (int i = 0; i < alias->nb_alias; i++) {
        if (strcmp(name, alias->info[i]->name) == 0) {
            printf_flush("%s\t%s\n", alias->info[i]->name,
                alias->info[i]->value);
            return;
        }
    }
}
