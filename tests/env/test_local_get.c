/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** test_local_get
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "env.h"

Test(get_local_value, should_return_value_for_existing_variable)
{
    shell_t shell;
    shell.local_size = 2;
    shell.local_vars = malloc(sizeof(char *) * 2);
    shell.local_vars[0] = strdup("LANG=fr_FR");
    shell.local_vars[1] = strdup("DEBUG=true");

    char *result = get_local_value(&shell, "LANG");
    cr_assert_str_eq(result, "fr_FR");

    free(shell.local_vars[0]);
    free(shell.local_vars[1]);
    free(shell.local_vars);
}

Test(get_local_value, should_return_null_for_nonexistent_variable)
{
    shell_t shell;
    shell.local_size = 1;
    shell.local_vars = malloc(sizeof(char *) * 1);
    shell.local_vars[0] = strdup("DEBUG=true");

    char *result = get_local_value(&shell, "VERSION");
    cr_assert_null(result);

    free(shell.local_vars[0]);
    free(shell.local_vars);
}

Test(get_local_value, should_return_null_if_var_is_null)
{
    shell_t shell = {.local_vars = NULL, .local_size = 0};
    cr_assert_null(get_local_value(&shell, NULL));
}

Test(get_local_value, should_return_null_if_shell_is_null)
{
    cr_assert_null(get_local_value(NULL, "DEBUG"));
}

Test(get_local_value, should_not_match_partial_prefix)
{
    shell_t shell;
    shell.local_size = 1;
    shell.local_vars = malloc(sizeof(char *) * 1);
    shell.local_vars[0] = strdup("DEBUGGER=on");

    char *result = get_local_value(&shell, "DEBUG");
    cr_assert_null(result);

    free(shell.local_vars[0]);
    free(shell.local_vars);
}