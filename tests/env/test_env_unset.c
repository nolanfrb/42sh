/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** test_env_unset
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "env.h"

Test(unset_env_value, should_remove_existing_variable)
{
    shell_t shell;
    shell.env_size = 3;
    shell.env_array = malloc(sizeof(char *) * 4);
    shell.env_array[0] = strdup("USER=loann");
    shell.env_array[1] = strdup("PATH=/bin");
    shell.env_array[2] = strdup("EDITOR=nano");
    shell.env_array[3] = NULL;

    unset_env_value(&shell, "PATH");

    cr_assert_eq(shell.env_size, 2);
    cr_assert_str_eq(shell.env_array[0], "USER=loann");
    cr_assert_str_eq(shell.env_array[1], "EDITOR=nano");
    cr_assert_null(shell.env_array[2]);

    free(shell.env_array[0]);
    free(shell.env_array[1]);
    free(shell.env_array);
}

Test(unset_env_value, should_do_nothing_if_variable_does_not_exist)
{
    shell_t shell;
    shell.env_size = 2;
    shell.env_array = malloc(sizeof(char *) * 3);
    shell.env_array[0] = strdup("USER=loann");
    shell.env_array[1] = strdup("EDITOR=vim");
    shell.env_array[2] = NULL;

    unset_env_value(&shell, "PATH");

    cr_assert_eq(shell.env_size, 2);
    cr_assert_str_eq(shell.env_array[0], "USER=loann");
    cr_assert_str_eq(shell.env_array[1], "EDITOR=vim");
    cr_assert_null(shell.env_array[2]);

    free(shell.env_array[0]);
    free(shell.env_array[1]);
    free(shell.env_array);
}

Test(unset_env_value, should_handle_null_shell_and_var)
{
    unset_env_value(NULL, "FOO");
    unset_env_value(&(shell_t){0}, NULL);
    cr_assert(1); // Ne doit pas segfault
}

Test(unset_env_value, should_not_match_prefix_only)
{
    shell_t shell;
    shell.env_size = 1;
    shell.env_array = malloc(sizeof(char *) * 2);
    shell.env_array[0] = strdup("PATHWAY=/weird/path");
    shell.env_array[1] = NULL;

    unset_env_value(&shell, "PATH");

    cr_assert_eq(shell.env_size, 1);
    cr_assert_str_eq(shell.env_array[0], "PATHWAY=/weird/path");
    cr_assert_null(shell.env_array[1]);

    free(shell.env_array[0]);
    free(shell.env_array);
}