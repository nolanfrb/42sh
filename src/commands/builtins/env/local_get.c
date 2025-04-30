/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** local_get
*/

#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *get_local_value(shell_t *shell, const char *var)
{
    int len;
    int i = 0;

    if (!shell || !var)
        return NULL;
    len = strlen(var);
    while (i < shell->local_size) {
        if (strncmp(shell->local_vars[i], var, len) == 0 &&
            shell->local_vars[i][len] == '=') {
            return shell->local_vars[i] + len + 1;
        }
        i++;
    }
    return NULL;
}
