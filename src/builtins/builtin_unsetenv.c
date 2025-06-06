/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_unsetenv
*/

#include "shell.h"
#include "env.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int builtin_unsetenv(shell_t *shell, char **args)
{
    if (!shell || !args || !args[0])
        return 1;
    if (!args[1]) {
        printf_flush("unsetenv: Too few arguments.\n");
        shell->exit_code = 1;
        return 1;
    }
    if (args[2]) {
        printf_flush("unsetenv: Too many arguments.\n");
        shell->exit_code = 1;
        return 1;
    }
    unset_env_value(shell, args[1]);
    return 0;
}
