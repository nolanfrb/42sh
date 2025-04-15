/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_handle_delimiter
*/

#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

Test(handle_delimiter, should_start_new_word_on_non_delimiter)
{
    word_info_t info = {.start = -1, .word_idx = 0, .words = malloc(sizeof(char *) * 3)};
    int i = 0;

    char *line = "a";
    char *delim = " ";

    int ret = handle_delimiter(line, &i, &info, delim);

    cr_assert_eq(ret, 0);
    cr_assert_eq(info.start, 0);

    free(info.words);
}

Test(handle_delimiter, should_finalize_word_on_delimiter)
{
    word_info_t info = {.start = 0, .word_idx = 0, .words = malloc(sizeof(char *) * 3)};
    int i = 1;

    char *line = "a ";
    char *delim = " ";

    int ret = handle_delimiter(line, &i, &info, delim);

    cr_assert_eq(ret, 0);
    cr_assert_eq(info.word_idx, 1);
    cr_assert_str_eq(info.words[0], "a");
    cr_assert_eq(info.start, -1);

    free(info.words[0]);
    free(info.words);
}

Test(handle_delimiter, should_do_nothing_on_delimiter_if_start_is_minus_one)
{
    word_info_t info = {.start = -1, .word_idx = 0, .words = malloc(sizeof(char *) * 3)};
    int i = 0;

    char *line = " ";
    char *delim = " ";

    int ret = handle_delimiter(line, &i, &info, delim);

    cr_assert_eq(ret, 0);
    cr_assert_eq(info.word_idx, 0);
    cr_assert_eq(info.start, -1);

    free(info.words);
}
