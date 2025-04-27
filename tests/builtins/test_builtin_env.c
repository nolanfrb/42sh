/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_builtin_env
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"
#include "builtins.h"

void redirect_all_stdout_env(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(builtin_env, should_return_0_if_shell_is_null)
{
    cr_assert_eq(builtin_env(NULL, NULL), 0);
}

Test(builtin_env, should_return_0_if_env_array_is_null)
{
    shell_t shell = {0};

    cr_assert_eq(builtin_env(&shell, NULL), 0);
}

Test(builtin_env, should_print_all_env_variables, .init = redirect_all_stdout_env)
{
    shell_t shell = {0};
    shell.env_array = malloc(sizeof(char *) * 4);
    shell.env_array[0] = strdup("USER=loann");
    shell.env_array[1] = strdup("HOME=/home/loann");
    shell.env_array[2] = strdup("PATH=/usr/bin");
    shell.env_array[3] = NULL;
    shell.env_size = 3;

    builtin_env(&shell, NULL);

    cr_assert_stdout_eq_str(
        "USER=loann\n"
        "HOME=/home/loann\n"
        "PATH=/usr/bin\n"
    );

    free(shell.env_array[0]);
    free(shell.env_array[1]);
    free(shell.env_array[2]);
    free(shell.env_array);
}

Test(builtin_env, should_not_fail_with_empty_env, .init = redirect_all_stdout_env)
{
    shell_t shell = {0};
    shell.env_array = malloc(sizeof(char *));
    shell.env_array[0] = NULL;
    shell.env_size = 0;

    builtin_env(&shell, NULL);

    cr_assert_stdout_eq_str("");

    free(shell.env_array);
}