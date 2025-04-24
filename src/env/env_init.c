/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** env_init
*/

#include "shell.h"
#include <stdlib.h>
#include <string.h>

static int count_env_size(char **env)
{
    int size = 0;

    while (env[size])
        size++;
    return size;
}

static void free_env_array_on_failure(char **env_array, int index)
{
    while (index > 0) {
        free(env_array[index - 1]);
        index--;
    }
    free(env_array);
}

static char **allocate_env_array(int env_size)
{
    char **env_array = malloc(sizeof(char *) * (env_size + 1));

    if (!env_array)
        return NULL;
    return env_array;
}

static char **copy_env_array(char **env, int env_size)
{
    char **env_array = allocate_env_array(env_size);
    int i = 0;

    if (!env_array)
        return NULL;
    while (i < env_size) {
        env_array[i] = strdup(env[i]);
        if (!env_array[i]) {
            free_env_array_on_failure(env_array, i);
            return NULL;
        }
        i++;
    }
    env_array[env_size] = NULL;
    return env_array;
}

static bool init_shell_env(shell_t *shell, char **env)
{
    shell->env_size = count_env_size(env);
    shell->env_array = copy_env_array(env, shell->env_size);
    if (!shell->env_array)
        return false;
    return true;
}

static bool init_shell_locals(shell_t *shell)
{
    shell->local_vars = malloc(sizeof(char *));
    if (!shell->local_vars)
        return false;
    shell->local_vars[0] = NULL;
    shell->local_size = 0;
    return true;
}

shell_t *init_shell(char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (!shell)
        return NULL;
    shell->env_size = count_env_size(env);
    shell->env_array = copy_env_array(env, shell->env_size);
    shell->history = init_history();
    if (!init_shell_env(shell, env)) {
        free(shell);
        return NULL;
    }
    if (!init_shell_locals(shell)) {
        free(shell);
        return NULL;
    }
    shell->local_size = 0;
    shell->exit_code = 0;
    return shell;
}
