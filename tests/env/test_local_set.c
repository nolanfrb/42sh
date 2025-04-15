/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** test_local_set
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "env.h"

Test(set_local_value, should_add_new_local_variable)
{
    shell_t shell = {
        .local_vars = malloc(sizeof(char *) * 1),
        .local_size = 0
    };
    shell.local_vars[0] = NULL;

    set_local_value(&shell, "DEBUG", "true");

    cr_assert_eq(shell.local_size, 1);
    cr_assert_str_eq(shell.local_vars[0], "DEBUG=true");
    cr_assert_null(shell.local_vars[1]);

    free(shell.local_vars[0]);
    free(shell.local_vars);
}

Test(set_local_value, should_update_existing_local_variable)
{
    shell_t shell = {
        .local_size = 1,
        .local_vars = malloc(sizeof(char *) * 2)
    };
    shell.local_vars[0] = strdup("MODE=dev");
    shell.local_vars[1] = NULL;

    set_local_value(&shell, "MODE", "prod");

    cr_assert_eq(shell.local_size, 1);
    cr_assert_str_eq(shell.local_vars[0], "MODE=prod");

    free(shell.local_vars[0]);
    free(shell.local_vars);
}

Test(set_local_value, should_ignore_null_shell)
{
    set_local_value(NULL, "FOO", "BAR");
    cr_assert(1); // Ne doit pas segfault
}

Test(set_local_value, should_ignore_null_var)
{
    shell_t shell = {.local_size = 0, .local_vars = NULL};
    set_local_value(&shell, NULL, "value");
    cr_assert(1);
}

Test(set_local_value, should_ignore_null_value)
{
    shell_t shell = {.local_size = 0, .local_vars = NULL};
    set_local_value(&shell, "VAR", NULL);
    cr_assert(1);
}