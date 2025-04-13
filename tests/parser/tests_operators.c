/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** tests_operators
*/

#include <criterion/criterion.h>
#include "ast.h"

Test(is_special_op, null_operator)
{
    cr_assert_eq(is_special_op(NULL), false);
}

Test(is_special_op, empty_operator)
{
    cr_assert_eq(is_special_op(""), false);
}

Test(is_redirect_op, null_operator)
{
    cr_assert_eq(is_redirect_op(NULL), false);
}

Test(is_redirect_op, empty_operator)
{
    cr_assert_eq(is_redirect_op(""), false);
}