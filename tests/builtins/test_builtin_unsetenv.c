/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_builtin_unsetenv
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"
#include "builtins.h"

void redirect_all_stdout_unsetenv(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(builtin_unsetenv, should_return_1_if_shell_is_null)
{
    cr_assert_eq(builtin_unsetenv(NULL, (char*[]){"unsetenv", "VAR", NULL}), 1);
}

Test(builtin_unsetenv, should_return_1_if_args_is_null)
{
    shell_t shell = {0};
    cr_assert_eq(builtin_unsetenv(&shell, NULL), 1);
}

Test(builtin_unsetenv, should_return_1_if_no_arguments, .init = redirect_all_stdout_unsetenv)
{
    shell_t shell = {0};
    char *args[] = {"unsetenv", NULL};

    int ret = builtin_unsetenv(&shell, args);

    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit_code, 1);
    cr_assert_stdout_eq_str("unsetenv: Too few arguments.\n");
}

Test(builtin_unsetenv, should_return_1_if_too_many_arguments, .init = redirect_all_stdout_unsetenv)
{
    shell_t shell = {0};
    char *args[] = {"unsetenv", "VAR", "EXTRA", NULL};

    int ret = builtin_unsetenv(&shell, args);

    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit_code, 1);
    cr_assert_stdout_eq_str("unsetenv: Too many arguments.\n");
}

Test(builtin_unsetenv, should_call_unset_env_value_when_arguments_are_valid)
{
    shell_t shell = {0};
    char *args[] = {"unsetenv", "VAR", NULL};

    int ret = builtin_unsetenv(&shell, args);

    cr_assert_eq(ret, 0);
}