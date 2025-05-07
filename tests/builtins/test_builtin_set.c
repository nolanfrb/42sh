/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_builtin_set
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "src/builtins/builtin_set.c"
#include "builtins.h"
#include "shell.h"
#include <stdlib.h>

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(builtin_set, no_args_prints_nothing, .init = redirect_all_stdout)
{
    shell_t shell = {0};
    char *args[] = {"set", NULL};

    int ret = builtin_set(&shell, args);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("");
}

Test(builtin_set, set_single_variable_with_value, .init = redirect_all_stdout)
{
    shell_t shell = {0};
    char *args[] = {"set", "foo=bar", NULL};

    shell.local_vars = NULL;
    shell.local_size = 0;

    int ret = builtin_set(&shell, args);

    cr_assert_eq(ret, 0);
    cr_assert_not_null(shell.local_vars);
    cr_assert_str_eq(shell.local_vars[0], "foo=bar");

    free(shell.local_vars[0]);
    free(shell.local_vars);
}

Test(builtin_set, set_multiple_variables_mixed, .init = redirect_all_stdout)
{
    shell_t shell = {0};
    char *args[] = {"set", "alpha=1", "beta", "gamma=3", NULL};

    shell.local_vars = NULL;
    shell.local_size = 0;

    builtin_set(&shell, args);

    cr_assert_str_eq(shell.local_vars[0], "alpha=1");
    cr_assert_str_eq(shell.local_vars[1], "beta=");
    cr_assert_str_eq(shell.local_vars[2], "gamma=3");

    for (int i = 0; i < shell.local_size; i++)
        free(shell.local_vars[i]);
    free(shell.local_vars);
}

Test(builtin_set, handle_set_without_value_invalid_name, .init = redirect_all_stdout)
{
    shell_t shell = {0};
    char *args[] = {"set", "@invalid", NULL};

    shell.local_vars = NULL;
    shell.local_size = 0;

    builtin_set(&shell, args);

    cr_assert_eq(shell.local_size, 0);
    if (shell.local_vars)
        free(shell.local_vars);
}
