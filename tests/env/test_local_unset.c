/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** test_local_unset
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "env.h"

Test(unset_local_value, should_remove_existing_local_variable)
{
    shell_t shell;
    shell.local_size = 3;
    shell.local_vars = malloc(sizeof(char *) * 4);
    shell.local_vars[0] = strdup("LANG=fr");
    shell.local_vars[1] = strdup("DEBUG=true");
    shell.local_vars[2] = strdup("MODE=dev");
    shell.local_vars[3] = NULL;

    unset_local_value(&shell, "DEBUG");

    cr_assert_eq(shell.local_size, 2);
    cr_assert_str_eq(shell.local_vars[0], "LANG=fr");
    cr_assert_str_eq(shell.local_vars[1], "MODE=dev");
    cr_assert_null(shell.local_vars[2]);

    free(shell.local_vars[0]);
    free(shell.local_vars[1]);
    free(shell.local_vars);
}

Test(unset_local_value, should_do_nothing_if_variable_does_not_exist)
{
    shell_t shell;
    shell.local_size = 2;
    shell.local_vars = malloc(sizeof(char *) * 3);
    shell.local_vars[0] = strdup("LANG=fr");
    shell.local_vars[1] = strdup("MODE=prod");
    shell.local_vars[2] = NULL;

    unset_local_value(&shell, "DEBUG");

    cr_assert_eq(shell.local_size, 2);
    cr_assert_str_eq(shell.local_vars[0], "LANG=fr");
    cr_assert_str_eq(shell.local_vars[1], "MODE=prod");
    cr_assert_null(shell.local_vars[2]);

    free(shell.local_vars[0]);
    free(shell.local_vars[1]);
    free(shell.local_vars);
}

Test(unset_local_value, should_handle_null_shell_and_var)
{
    unset_local_value(NULL, "VAR");
    unset_local_value(&(shell_t){0}, NULL);
    cr_assert(1); // Ne doit pas segfault
}

Test(unset_local_value, should_not_match_partial_prefix)
{
    shell_t shell;
    shell.local_size = 1;
    shell.local_vars = malloc(sizeof(char *) * 2);
    shell.local_vars[0] = strdup("VERSIONNING=active");
    shell.local_vars[1] = NULL;

    unset_local_value(&shell, "VERSION");

    cr_assert_eq(shell.local_size, 1);
    cr_assert_str_eq(shell.local_vars[0], "VERSIONNING=active");
    cr_assert_null(shell.local_vars[1]);

    free(shell.local_vars[0]);
    free(shell.local_vars);
}