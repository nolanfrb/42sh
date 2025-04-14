/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_lexer
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

Test(lexer, should_split_simple_command)
{
    char **tokens = lexer("ls -la");

    cr_assert_not_null(tokens);
    cr_assert_str_eq(tokens[0], "ls");
    cr_assert_str_eq(tokens[1], "-la");
    cr_assert_null(tokens[2]);

    free(tokens[0]);
    free(tokens[1]);
    free(tokens);
}

Test(lexer, should_handle_special_token)
{
    char **tokens = lexer("echo && ls");

    cr_assert_not_null(tokens);
    cr_assert_str_eq(tokens[0], "echo");
    cr_assert_str_eq(tokens[1], "&&");
    cr_assert_str_eq(tokens[2], "ls");
    cr_assert_null(tokens[3]);

    for (int i = 0; i < 3; i++)
        free(tokens[i]);
    free(tokens);
}

Test(lexer, should_handle_command_with_trailing_word)
{
    char **tokens = lexer("echo test");

    cr_assert_not_null(tokens);
    cr_assert_str_eq(tokens[0], "echo");
    cr_assert_str_eq(tokens[1], "test");
    cr_assert_null(tokens[2]);

    free(tokens[0]);
    free(tokens[1]);
    free(tokens);
}