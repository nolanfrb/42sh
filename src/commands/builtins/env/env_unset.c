/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** env_unset
*/

#include "shell.h"
#include <stdlib.h>
#include <string.h>

static int find_env_index(shell_t *shell, const char *var)
{
    int len = strlen(var);
    int i = 0;

    while (i < shell->env_size) {
        if (strncmp(shell->env_array[i], var, len) == 0 &&
            shell->env_array[i][len] == '=')
            return i;
        i++;
    }
    return -1;
}

static void shift_env_variables(shell_t *shell, int index)
{
    int i = index;

    while (i < shell->env_size - 1) {
        shell->env_array[i] = shell->env_array[i + 1];
        i++;
    }
    shell->env_array[shell->env_size - 1] = NULL;
    shell->env_size--;
}

void unset_env_value(shell_t *shell, const char *var)
{
    int index;

    if (!shell || !var)
        return;
    index = find_env_index(shell, var);
    if (index == -1)
        return;
    free(shell->env_array[index]);
    shift_env_variables(shell, index);
}
