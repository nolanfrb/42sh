/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** local_unset
*/

#include "shell.h"
#include <stdlib.h>
#include <string.h>

static int find_local_index(shell_t *shell, const char *var)
{
    int len = strlen(var);
    int i = 0;

    while (i < shell->local_size) {
        if (strncmp(shell->local_vars[i], var, len) == 0 &&
            shell->local_vars[i][len] == '=')
            return i;
        i++;
    }
    return -1;
}

static void shift_local_variables(shell_t *shell, int index)
{
    int i = index;

    while (i < shell->local_size - 1) {
        shell->local_vars[i] = shell->local_vars[i + 1];
        i++;
    }
    shell->local_vars[shell->local_size - 1] = NULL;
    shell->local_size--;
}

void unset_local_value(shell_t *shell, const char *var)
{
    int index;

    if (!shell || !var)
        return;
    index = find_local_index(shell, var);
    if (index == -1)
        return;
    free(shell->local_vars[index]);
    shift_local_variables(shell, index);
}
