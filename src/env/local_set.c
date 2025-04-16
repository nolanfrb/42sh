/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** local_set
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"

static int update_existing_local_var(shell_t *shell, const char *var,
    char *new_var, int len)
{
    int i = 0;

    while (i < shell->local_size) {
        if (strncmp(shell->local_vars[i], var, len) == 0 &&
            shell->local_vars[i][len] == '=') {
            free(shell->local_vars[i]);
            shell->local_vars[i] = new_var;
            return 1;
        }
        i++;
    }
    return 0;
}

static int add_new_local_var(shell_t *shell, char *new_var)
{
    size_t new_size = sizeof(char *) * (shell->local_size + 2);
    char **new_local_array = realloc(shell->local_vars, new_size);

    if (!new_local_array) {
        free(new_var);
        return 84;
    }
    shell->local_vars = new_local_array;
    shell->local_vars[shell->local_size] = new_var;
    shell->local_vars[shell->local_size + 1] = NULL;
    shell->local_size++;
    return 0;
}

void set_local_value(shell_t *shell, const char *var, const char *value)
{
    char *new_var;
    int len;

    if (!shell || !var || !value)
        return;
    len = strlen(var);
    new_var = malloc(len + strlen(value) + 2);
    if (!new_var)
        return;
    strcpy(new_var, var);
    strcat(new_var, "=");
    strcat(new_var, value);
    if (update_existing_local_var(shell, var, new_var, len))
        return;
    add_new_local_var(shell, new_var);
}
