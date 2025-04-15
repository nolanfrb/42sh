/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** test_env_set
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "env.h"

Test(set_env_value, should_add_new_variable)
{
    shell_t shell = {
        .env_array = malloc(sizeof(char *) * 1),
        .env_size = 0
    };
    shell.env_array[0] = NULL;

    set_env_value(&shell, "EDITOR", "vim");

    cr_assert_eq(shell.env_size, 1);
    cr_assert_str_eq(shell.env_array[0], "EDITOR=vim");
    cr_assert_null(shell.env_array[1]);

    free(shell.env_array[0]);
    free(shell.env_array);
}

Test(set_env_value, should_update_existing_variable)
{
    shell_t shell = {
        .env_size = 1,
        .env_array = malloc(sizeof(char *) * 2)
    };
    shell.env_array[0] = strdup("EDITOR=nano");
    shell.env_array[1] = NULL;

    set_env_value(&shell, "EDITOR", "vim");

    cr_assert_eq(shell.env_size, 1);
    cr_assert_str_eq(shell.env_array[0], "EDITOR=vim");

    free(shell.env_array[0]);
    free(shell.env_array);
}

Test(set_env_value, should_ignore_null_shell)
{
    set_env_value(NULL, "FOO", "BAR");
    cr_assert(1); // Ne doit pas segfault
}

Test(set_env_value, should_ignore_null_var)
{
    shell_t shell = {.env_size = 0, .env_array = NULL};
    set_env_value(&shell, NULL, "value");
    cr_assert(1); // Ne doit pas segfault
}

Test(set_env_value, should_ignore_null_value)
{
    shell_t shell = {.env_size = 0, .env_array = NULL};
    set_env_value(&shell, "VAR", NULL);
    cr_assert(1); // Ne doit pas segfault
}