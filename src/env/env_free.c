/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** env_free
*/

#include <stdlib.h>
#include "shell.h"


static void free_env_array(shell_t *shell)
{
    int i = 0;

    if (!shell->env_array)
        return;
    while (i < shell->env_size) {
        free(shell->env_array[i]);
        i++;
    }
    free(shell->env_array);
}

static void free_local_vars(shell_t *shell)
{
    int i = 0;

    if (!shell->local_vars)
        return;
    while (i < shell->local_size) {
        free(shell->local_vars[i]);
        i++;
    }
    free(shell->local_vars);
}

void free_shell(shell_t *shell)
{
    if (!shell)
        return;
    free_env_array(shell);
    free_local_vars(shell);
    free(shell);
}
