/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** env_free
*/

#include <stdlib.h>
#include "shell.h"



static void free_env_array(char **env_array, int env_size)
{
    int i = 0;

    if (!env_array)
        return;
    while (i < env_size) {
        if (env_array[i])
            free(env_array[i]);
        i++;
    }
    free(env_array);
}

static void free_local_vars(char **local_vars, int local_size)
{
    int i = 0;

    if (!local_vars)
        return;
    while (i < local_size) {
        if (local_vars[i])
            free(local_vars[i]);
        i++;
    }
    free(local_vars);
}

void free_shell(shell_t *shell)
{
    if (!shell)
        return;
    free_env_array(shell->env_array, shell->env_size);
    free_local_vars(shell->local_vars, shell->local_size);
    free_ast(shell->ast);
    free(shell);
}
