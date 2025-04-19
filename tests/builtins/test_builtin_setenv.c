/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_builtin_setenv
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "src/builtins/builtin_setenv.c"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(is_valid_env_name, should_accept_valid_names)
{
    cr_assert_eq(is_valid_env_name("VAR123"), 1);
    cr_assert_eq(is_valid_env_name("_VALID"), 1);
    cr_assert_eq(is_valid_env_name("a_b_c"), 1);
}

Test(is_valid_env_name, should_reject_invalid_names)
{
    cr_assert_eq(is_valid_env_name(""), 0);
    cr_assert_eq(is_valid_env_name(NULL), 0);
    cr_assert_eq(is_valid_env_name("1invalid"), 1);
    cr_assert_eq(is_valid_env_name("VAR!NAME"), 0);
}

Test(handle_setenv_errors, should_detect_too_many_arguments, .init = redirect_all_stdout)
{
    shell_t shell = {0};
    char *args[] = {"setenv", "VAR", "value1", "value2", NULL};

    int ret = handle_setenv_errors(&shell, args);

    cr_assert_eq(ret, 84);
    cr_assert_eq(shell.exit_code, 1);
    cr_assert_stdout_eq_str("setenv: Too many arguments.\n");
}

Test(handle_setenv_errors, should_detect_invalid_name, .init = redirect_all_stdout)
{
    shell_t shell = {0};
    char *args[] = {"setenv", "INVAL!D", NULL};

    int ret = handle_setenv_errors(&shell, args);

    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit_code, 1);
    cr_assert_stdout_eq_str("setenv: Variable name must contain alphanumeric characters.\n");
}

Test(handle_setenv_errors, should_accept_valid_input)
{
    shell_t shell = {0};
    char *args[] = {"setenv", "VALID_NAME", NULL};

    int ret = handle_setenv_errors(&shell, args);

    cr_assert_eq(ret, 0);
    cr_assert_eq(shell.exit_code, 0);
}

Test(print_environment, should_print_all_environment_variables, .init = redirect_all_stdout)
{
    shell_t shell;
    shell.env_array = malloc(sizeof(char *) * 3);
    shell.env_array[0] = strdup("USER=loann");
    shell.env_array[1] = strdup("PATH=/usr/bin");
    shell.env_array[2] = NULL;

    print_environment(&shell);

    cr_assert_stdout_eq_str("USER=loann\nPATH=/usr/bin\n");

    free(shell.env_array[0]);
    free(shell.env_array[1]);
    free(shell.env_array);
}


Test(builtin_setenv, should_return_1_if_shell_is_null)
{
    cr_assert_eq(builtin_setenv(NULL, (char*[]){"setenv", "VAR", "VALUE", NULL}), 1);
}

Test(builtin_setenv, should_return_1_if_args_is_null)
{
    shell_t shell = {0};
    cr_assert_eq(builtin_setenv(&shell, NULL), 1);
}

Test(builtin_setenv, should_print_env_if_no_arguments, .init = redirect_all_stdout)
{
    shell_t shell;
    shell.env_array = malloc(sizeof(char *) * 3);
    shell.env_array[0] = strdup("USER=loann");
    shell.env_array[1] = strdup("PATH=/usr/bin");
    shell.env_array[2] = NULL;

    int ret = builtin_setenv(&shell, (char*[]){"setenv", NULL});

    cr_assert_eq(ret, 0);
    cr_assert_stdout_eq_str("USER=loann\nPATH=/usr/bin\n");

    free(shell.env_array[0]);
    free(shell.env_array[1]);
    free(shell.env_array);
}

Test(builtin_setenv, should_fail_when_handle_setenv_errors_fails, .init = redirect_all_stdout)
{
    shell_t shell = {0};
    char *args[] = {"setenv", "INVAL!D", NULL};

    int ret = builtin_setenv(&shell, args);

    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit_code, 1);
}