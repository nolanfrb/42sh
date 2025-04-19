/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_echo_utils
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include "builtins.h"
#include "shell.h"
#include "src/builtins/echo_utils.c"

void redirect_all_stdout_echo(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(is_double_quoted, should_detect_correctly)
{
    cr_assert_eq(is_double_quoted("\"hello\""), 1);
    cr_assert_eq(is_double_quoted("\"\""), 1);
    cr_assert_eq(is_double_quoted("hello"), 0);
    cr_assert_eq(is_double_quoted("'hello'"), 0);
}

Test(is_single_quoted, should_detect_correctly)
{
    cr_assert_eq(is_single_quoted("'hello'"), 1);
    cr_assert_eq(is_single_quoted("''"), 1);
    cr_assert_eq(is_single_quoted("hello"), 0);
    cr_assert_eq(is_single_quoted("\"hello\""), 0);
}

Test(print_single_quoted, should_remove_quotes, .init = redirect_all_stdout_echo)
{
    print_single_quoted("'hello'");
    cr_assert_stdout_eq_str("hello");
}


Test(handle_double_quotes, should_remove_and_print_string, .init = redirect_all_stdout_echo)
{
    shell_t shell = {0};
    handle_double_quotes(&shell, "\"hello\"");
    cr_assert_stdout_eq_str("hello");
}

Test(remove_quotes, should_return_unquoted_string)
{
    char *result = remove_quotes("\"hello\"");
    cr_assert_str_eq(result, "hello");
    free(result);
}

Test(get_env_value, should_find_value)
{
    shell_t shell = {0};
    shell.env_array = malloc(sizeof(char *) * 2);
    shell.env_array[0] = strdup("MYVAR=value");
    shell.env_array[1] = NULL;
    shell.env_size = 1;
    char *value = get_env_value(&shell, "MYVAR");

    cr_assert_str_eq(value, "value");

    free(shell.env_array[0]);
    free(shell.env_array);
}

Test(print_env_variable, should_print_value_of_existing_variable, .init = redirect_all_stdout_echo)
{
    shell_t shell = {0};
    shell.env_array = malloc(sizeof(char *) * 2);
    shell.env_array[0] = strdup("MYVAR=value");
    shell.env_array[1] = NULL;
    shell.env_size = 1;

    print_env_variable(&shell, "$MYVAR");

    cr_assert_stdout_eq_str("value");
    cr_assert_eq(shell.exit_code, 0);

    free(shell.env_array[0]);
    free(shell.env_array);
}

Test(print_env_variable, should_print_error_when_variable_undefined, .init = redirect_all_stdout_echo)
{
    shell_t shell = {0};
    shell.env_array = malloc(sizeof(char *) * 1);
    shell.env_array[0] = NULL;

    print_env_variable(&shell, "$UNDEF");

    cr_assert_stdout_eq_str("UNDEF: Undefined variable.\n");
    cr_assert_eq(shell.exit_code, 1);

    free(shell.env_array);
}