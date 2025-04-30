/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_env
*/

#include "shell.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int builtin_env(shell_t *shell, char **args)
{
    int i = 0;

    (void)args;
    if (!shell || !shell->env_array)
        return 0;
    while (i < shell->env_size && shell->env_array[i]) {
        write(1, shell->env_array[i], strlen(shell->env_array[i]));
        write(1, "\n", 1);
        i++;
    }
    return 0;
}
