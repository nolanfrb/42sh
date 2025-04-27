/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_builtin_echo
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"
#include "builtins.h"
#include "src/builtins/builtin_echo.c"

void redirect_all_stdout_echo(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(builtin_echo, should_print_newline_if_no_arguments, .init = redirect_all_stdout_echo)
{
    shell_t shell = {0};
    char *args[] = {"echo", NULL};

    builtin_echo(&shell, args);

    cr_assert_stdout_eq_str("\n");
    cr_assert_eq(shell.exit_code, 0);
}

Test(builtin_echo, should_print_single_argument, .init = redirect_all_stdout_echo)
{
    shell_t shell = {0};
    char *args[] = {"echo", "hello", NULL};

    builtin_echo(&shell, args);

    cr_assert_stdout_eq_str("hello\n");
    cr_assert_eq(shell.exit_code, 0);
}

Test(builtin_echo, should_print_multiple_arguments_with_spaces, .init = redirect_all_stdout_echo)
{
    shell_t shell = {0};
    char *args[] = {"echo", "hello", "world", NULL};

    builtin_echo(&shell, args);

    cr_assert_stdout_eq_str("hello world\n");
    cr_assert_eq(shell.exit_code, 0);
}

Test(builtin_echo, should_handle_double_quoted_argument, .init = redirect_all_stdout_echo)
{
    shell_t shell = {0};
    char *args[] = {"echo", "\"hello\"", NULL};

    builtin_echo(&shell, args);

    cr_assert_stdout_eq_str("hello\n");
    cr_assert_eq(shell.exit_code, 0);
}

Test(builtin_echo, should_handle_single_quoted_argument, .init = redirect_all_stdout_echo)
{
    shell_t shell = {0};
    char *args[] = {"echo", "'hello'", NULL};

    builtin_echo(&shell, args);

    cr_assert_stdout_eq_str("hello\n");
    cr_assert_eq(shell.exit_code, 0);
}

Test(builtin_echo, should_handle_env_variable_expansion, .init = redirect_all_stdout_echo)
{
    shell_t shell = {0};
    char *args[] = {"echo", "$MYVAR", NULL};

    shell.env_array = malloc(sizeof(char *) * 2);
    shell.env_array[0] = strdup("MYVAR=value");
    shell.env_array[1] = NULL;
    shell.env_size = 1;

    builtin_echo(&shell, args);

    cr_assert_stdout_eq_str("value\n");
    cr_assert_eq(shell.exit_code, 0);

    free(shell.env_array[0]);
    free(shell.env_array);
}