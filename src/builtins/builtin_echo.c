/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_echo
*/

#include "shell.h"
#include "builtins.h"
#include "env.h"
#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void print_arg(shell_t *shell, char *arg)
{
    if (is_double_quoted(arg)) {
        handle_double_quotes(shell, arg);
        return;
    }
    if (is_single_quoted(arg)) {
        print_single_quoted(arg);
        return;
    }
    if (arg[0] == '$') {
        print_env_variable(shell, arg);
        return;
    }
    printf("%s", arg);
}

static void print_args(shell_t *shell, char **args)
{
    int i = 1;

    while (args[i]) {
        if (i > 1)
            printf(" ");
        print_arg(shell, args[i]);
        i++;
    }
    printf("\n");
}

int builtin_echo(shell_t *shell, char **args)
{
    if (!args[1]) {
        printf("\n");
        shell->exit_code = 0;
        return 0;
    }
    print_args(shell, args);
    shell->exit_code = 0;
    return 0;
}
