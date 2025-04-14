/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_count_words
*/

#include <criterion/criterion.h>
#include "lexer.h"

Test(count_words, should_count_simple_words)
{
    cr_assert_eq(count_words("echo hello", " "), 2);
    cr_assert_eq(count_words("ls -la", " "), 2);
}

Test(count_words, should_handle_multiple_spaces)
{
    cr_assert_eq(count_words("  echo   test ", " "), 2);
    cr_assert_eq(count_words("     ", " "), 0);
}

Test(count_words, should_count_special_tokens_as_words)
{
    cr_assert_eq(count_words("echo && ls", " "), 3); // echo, &&, ls
    cr_assert_eq(count_words("a||b", " "), 3);       // a, ||, b
    cr_assert_eq(count_words("x|y|z", " "), 5);      // x, |, y, |, z
}

Test(count_words, should_mix_words_and_special_tokens)
{
    cr_assert_eq(count_words("grep foo | wc -l", " "), 5); // grep, foo, |, wc, -l
    cr_assert_eq(count_words("cmd1 && cmd2 || cmd3", " "), 5);
}

Test(count_words, should_return_zero_on_empty_input)
{
    cr_assert_eq(count_words("", " "), 0);
    cr_assert_eq(count_words("   ", " "), 0);
}

// Test(count_words, should_handle_custom_delimiters)
// {
//     cr_assert_eq(count_words("a,b,c", ","), 3);
//     cr_assert_eq(count_words("a;b&&c", ";"), 4); // a, b, &&, c
// }