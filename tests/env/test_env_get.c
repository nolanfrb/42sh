/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** test_env_get
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "env.h"

Test(get_env_value, should_return_value_for_existing_variable)
{
    shell_t shell;
    shell.env_size = 2;
    shell.env_array = malloc(sizeof(char *) * 2);
    shell.env_array[0] = strdup("USER=loann");
    shell.env_array[1] = strdup("PATH=/usr/bin");

    char *result = get_env_value(&shell, "USER");
    cr_assert_str_eq(result, "loann");

    free(shell.env_array[0]);
    free(shell.env_array[1]);
    free(shell.env_array);
}

Test(get_env_value, should_return_null_for_nonexistent_variable)
{
    shell_t shell;
    shell.env_size = 2;
    shell.env_array = malloc(sizeof(char *) * 2);
    shell.env_array[0] = strdup("USER=loann");
    shell.env_array[1] = strdup("PATH=/usr/bin");

    char *result = get_env_value(&shell, "HOME");
    cr_assert_null(result);

    free(shell.env_array[0]);
    free(shell.env_array[1]);
    free(shell.env_array);
}

Test(get_env_value, should_return_null_if_var_is_null)
{
    shell_t shell = {.env_array = NULL, .env_size = 0};
    cr_assert_null(get_env_value(&shell, NULL));
}

Test(get_env_value, should_return_null_if_shell_is_null)
{
    cr_assert_null(get_env_value(NULL, "PATH"));
}

Test(get_env_value, should_not_match_prefix_only)
{
    shell_t shell;
    shell.env_size = 1;
    shell.env_array = malloc(sizeof(char *) * 1);
    shell.env_array[0] = strdup("PATHWAY=/some/dir");

    cr_assert_null(get_env_value(&shell, "PATH"));

    free(shell.env_array[0]);
    free(shell.env_array);
}