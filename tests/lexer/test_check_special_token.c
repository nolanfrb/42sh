/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_check_special_token
*/

#include <criterion/criterion.h>
#include "lexer.h"

Test(check_special_token, should_find_token_and_return_index)
{
    cr_assert_eq(check_special_token("&& ls", 0), 2);
    cr_assert_eq(check_special_token("|| echo", 0), 3);
    cr_assert_eq(check_special_token(">> file", 0), 4);
    cr_assert_eq(check_special_token("| grep", 0), 8);
}

Test(check_special_token, should_ignore_non_special_tokens)
{
    cr_assert_eq(check_special_token("abcd", 0), -1);
    cr_assert_eq(check_special_token("echo", 0), -1);
    cr_assert_eq(check_special_token("and", 0), -1);
}

Test(check_special_token, should_match_token_only_at_given_position)
{
    cr_assert_eq(check_special_token("ls && echo", 3), 2);
    cr_assert_eq(check_special_token("ls && echo", 0), -1);
}

Test(check_special_token, should_not_crash_on_empty_string)
{
    cr_assert_eq(check_special_token("", 0), -1);
}