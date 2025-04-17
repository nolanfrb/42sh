/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_setenv
*/

#include "shell.h"
#include "env.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>


static int is_valid_env_name(const char *name)
{
    int i = 0;

    if (!name || !name[0])
        return 0;
    while (name[i]) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||
            (name[i] >= 'a' && name[i] <= 'z') ||
            (name[i] >= '0' && name[i] <= '9') ||
            name[i] == '_'))
            return 0;
        i++;
    }
    return 1;
}

static int handle_setenv_errors(shell_t *shell, char **args)
{
    if (args[2] && args[3]) {
        printf("setenv: Too many arguments.\n");
        return 84;
    }
    if (!is_valid_env_name(args[1])) {
        printf("setenv: Variable name must contain alphanumeric characters."
        "\n");
        shell->exit_code = 1;
        return 1;
    }
    return 0;
}

static int print_environment(shell_t *shell)
{
    for (int i = 0; shell->env_array[i]; i++) {
        printf(shell->env_array[i]);
        putchar('\n');
    }
    return 0;
}

int builtin_setenv(shell_t *shell, char **args)
{
    if (!shell || !args || !args[0])
        return 84;
    if (!args[1])
        return print_environment(shell);
    if (handle_setenv_errors(shell, args) != 0)
        return 84;
    set_env_value(shell, args[1], args[2] ? args[2] : "");
    return 0;
}