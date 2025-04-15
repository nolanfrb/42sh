/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_extract_word
*/

#include <criterion/criterion.h>
#include <string.h>
#include "lexer.h"

Test(extract_word, should_extract_correct_substring)
{
    char *result = extract_word("hello world", 0, 5);
    cr_assert_str_eq(result, "hello");
    free(result);
}

Test(extract_word, should_extract_word_from_middle)
{
    char *result = extract_word("hello world", 6, 5);
    cr_assert_str_eq(result, "world");
    free(result);
}

Test(extract_word, should_handle_partial_extraction)
{
    char *result = extract_word("criterion", 1, 4);
    cr_assert_str_eq(result, "rite");
    free(result);
}

Test(extract_word, should_return_empty_string_if_len_zero)
{
    char *result = extract_word("hello", 2, 0);
    cr_assert_str_eq(result, "");
    free(result);
}
