/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** search_alias
*/

#include <string.h>
#include "ast.h"
#include "shell.h"

int search_alias(alias_t *alias, command_node_t *command, shell_t *shell)
{
    for (int i = 0; i < alias->nb_alias; i++) {
        if (strcmp(alias->info[i]->name, command->argv[0]) == 0) {
            return build_str(command, alias->info[i]->value, shell);
        }
    }
    return 0;
}
