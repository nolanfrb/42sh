/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** env_get
*/

#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *get_env_value(shell_t *shell, const char *var)
{
    int len;
    int i = 0;

    if (!shell || !var)
        return NULL;
    len = strlen(var);
    while (i < shell->env_size) {
        if (strncmp(shell->env_array[i], var, len) == 0 &&
            shell->env_array[i][len] == '=') {
            return shell->env_array[i] + len + 1;
        }
        i++;
    }
    return NULL;
}
