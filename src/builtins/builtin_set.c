/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_set
*/

#include "shell.h"
#include "builtins.h"
#include <string.h>
#include <stdio.h>

static int is_valid_local_name(const char *name)
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

static void print_single_local_variable(const char *var)
{
    char *equal_sign = strchr(var, '=');
    int name_len = 0;

    if (equal_sign) {
        name_len = equal_sign - var;
        printf("%.*s\t%s\n", name_len, var, equal_sign + 1);
    } else {
        printf("%s\n", var);
    }
}

static int print_local_variables(shell_t *shell)
{
    int i = 0;

    if (!shell || !shell->local_vars)
        return 0;
    while (shell->local_vars[i]) {
        print_single_local_variable(shell->local_vars[i]);
        i++;
    }
    return 0;
}

static void handle_set_with_value(shell_t *shell, const char *arg)
{
    char *equal_sign = strchr(arg, '=');
    int name_len = equal_sign - arg;
    char name[name_len + 1];
    const char *value = equal_sign + 1;

    strncpy(name, arg, name_len);
    name[name_len] = '\0';
    if (!is_valid_local_name(name))
        return;
    set_local_value(shell, name, value);
}

static void handle_set_without_value(shell_t *shell, const char *arg)
{
    if (!is_valid_local_name(arg))
        return;
    set_local_value(shell, arg, "");
}

int builtin_set(shell_t *shell, char **args)
{
    int i = 1;

    if (!shell || !args || !args[0])
        return 1;
    if (!args[1])
        return print_local_variables(shell);
    while (args[i]) {
        if (strchr(args[i], '='))
            handle_set_with_value(shell, args[i]);
        else
            handle_set_without_value(shell, args[i]);
        i++;
    }
    return 0;
}
