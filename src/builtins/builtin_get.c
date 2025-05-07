/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_get
*/

#include "shell.h"
#include "builtins.h"
#include <stdio.h>

int builtin_get(shell_t *shell, char **args)
{
    char *value = NULL;

    if (!shell || !args || !args[0])
        return 1;
    if (!args[1]) {
        printf_flush("get: Too few arguments.\n");
        shell->exit_code = 1;
        return 1;
    }
    for (int i = 1; args[i]; i++) {
        value = get_local_value(shell, args[i]);
        if (value)
            printf_flush("%s\n", value);
        else
            shell->exit_code = 1;
    }
    return 0;
}
