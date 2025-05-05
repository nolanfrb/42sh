/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** builtin_alias
*/

#include <string.h>
#include <stdio.h>
#include "alias.h"

static int update_existing_alias(alias_info_t *info, char *value)
{
    char *new_value = strdup(value);

    if (new_value == NULL)
        return 1;
    free(info->value);
    info->value = new_value;
    return 0;
}

static int realloc_alias_info(alias_t *alias)
{
    alias_info_t **new_info = NULL;

    new_info = malloc(sizeof(alias_info_t *) * (alias->nb_alias + 1));
    if (new_info == NULL)
        return 1;
    for (int i = 0; i < alias->nb_alias; i++) {
        new_info[i] = alias->info[i];
    }
    free(alias->info);
    alias->info = new_info;
    return 0;
}

static int create_new_alias(alias_t *alias, char *name, char *value)
{
    alias_info_t *info = NULL;

    if (realloc_alias_info(alias) != 0)
        return 1;
    info = malloc(sizeof(alias_info_t));
    if (info == NULL)
        return 1;
    info->name = strdup(name);
    info->value = strdup(value);
    if (info->name == NULL || info->value == NULL) {
        free(info->name);
        free(info->value);
        free(info);
        return 1;
    }
    alias->info[alias->nb_alias] = info;
    alias->nb_alias++;
    return 0;
}

int add_alias(alias_t *alias, char *alias_name, char *alias_value)
{
    for (int i = 0; i < alias->nb_alias; i++) {
        if (strcmp(alias->info[i]->name, alias_name) == 0)
            return update_existing_alias(alias->info[i], alias_value);
    }
    return create_new_alias(alias, alias_name, alias_value);
}

int builtin_alias(shell_t *shell, char **args)
{
    alias_t *alias = shell->alias;

    parse_alias_args(alias, args);
    return 0;
}
