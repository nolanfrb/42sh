/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** build_str
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "shell.h"

static char *append_args(char *base, char **args)
{
    char *new_str = NULL;
    size_t len = 0;
    int i = 1;

    while (args[i] != NULL) {
        len = strlen(base) + strlen(args[i]) + 2;
        new_str = malloc(len);
        if (!new_str)
            return NULL;
        sprintf(new_str, "%s %s", base, args[i]);
        free(base);
        base = new_str;
        i++;
    }
    return base;
}

int build_str(command_node_t *command, char *alias_value, shell_t *shell)
{
    char *str = NULL;

    if (!command || !alias_value)
        return -1;
    str = strdup(alias_value);
    if (!str)
        return -1;
    str = append_args(str, command->argv);
    if (!str)
        return -1;
    shell->alias->state = ALIAS;
    handle_user_input(shell, str);
    free(str);
    return shell->exit_code;
}
