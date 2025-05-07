/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_unset_local
*/

#include "shell.h"
#include "builtins.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int builtin_unset_local(shell_t *shell, char **args)
{
    if (!shell || !args || !args[0])
        return 1;
    if (!args[1]) {
        printf_flush("unset: Too few arguments.\n");
        shell->exit_code = 1;
        return 1;
    }
    for (int i = 1; args[i]; i++)
        unset_local_value(shell, args[i]);
    return 0;
}
