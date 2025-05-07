

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Unit tests for builtin_get
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(builtin_get, get_existing_variable, .init = redirect_all_stdout)
{
    shell_t shell = {0};
    char *args[] = {"get", "foo", NULL};

    shell.local_vars = NULL;
    shell.local_size = 0;
    set_local_value(&shell, "foo", "bar");

    int ret = builtin_get(&shell, args);

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("bar\n");
}

Test(builtin_get, get_nonexistent_variable, .init = redirect_all_stdout)
{
    shell_t shell = {0};
    char *args[] = {"get", "missing", NULL};

    shell.local_vars = NULL;
    shell.local_size = 0;

    int ret = builtin_get(&shell, args);

    cr_assert_eq(ret, 0);
    cr_assert_eq(shell.exit_code, 1);
    cr_assert_stdout_eq_str("");
}

Test(builtin_get, no_argument, .init = redirect_all_stdout)
{
    shell_t shell = {0};
    char *args[] = {"get", NULL};

    int ret = builtin_get(&shell, args);

    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit_code, 1);
    cr_assert_stdout_eq_str("get: Too few arguments.\n");
}