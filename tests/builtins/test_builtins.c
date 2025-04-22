/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_builtins
*/

#include <criterion/criterion.h>
#include "builtins.h"
#include "command.h"
#include "shell.h"

Test(get_builtins, should_return_valid_builtins_list)
{
    const builtin_t *list = get_builtins();

    cr_assert_not_null(list, "Builtins list should not be NULL");

    cr_assert_str_eq(list[0].name, "cd");
    cr_assert_not_null(list[0].func);

    cr_assert_str_eq(list[1].name, "exit");
    cr_assert_not_null(list[1].func);

    cr_assert_str_eq(list[2].name, "setenv");
    cr_assert_not_null(list[2].func);

    cr_assert_str_eq(list[3].name, "unsetenv");
    cr_assert_not_null(list[3].func);

    cr_assert_str_eq(list[4].name, "env");
    cr_assert_not_null(list[4].func);

    cr_assert_str_eq(list[5].name, "echo");
    cr_assert_not_null(list[5].func);

    cr_assert_null(list[6].name, "Last builtin name should be NULL");
    cr_assert_null(list[6].func, "Last builtin function should be NULL");
}