/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_handle_special_token
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

Test(handle_special_token, should_add_only_special_token_if_no_word_in_progress)
{
    char *line = "&&";
    int i = 0;
    word_info_t info = {.start = -1, .word_idx = 0, .words = malloc(sizeof(char *) * 3)};

    int ret = handle_special_token(line, &i, &info);

    cr_assert_eq(ret, 0);
    cr_assert_eq(info.word_idx, 1);
    cr_assert_str_eq(info.words[0], "&&");
    cr_assert_eq(i, 1);

    free(info.words[0]);
    free(info.words);
}

Test(handle_special_token, should_add_previous_word_then_special_token)
{
    char *line = "ls&&";
    int i = 2;
    word_info_t info = {.start = 0, .word_idx = 0, .words = malloc(sizeof(char *) * 3)};

    int ret = handle_special_token(line, &i, &info);

    cr_assert_eq(ret, 0);
    cr_assert_eq(info.word_idx, 2);
    cr_assert_str_eq(info.words[0], "ls");
    cr_assert_str_eq(info.words[1], "&&");
    cr_assert_eq(i, 3);

    free(info.words[0]);
    free(info.words[1]);
    free(info.words);
}

Test(handle_special_token, should_return_84_if_not_a_special_token)
{
    char *line = "ls";
    int i = 0;
    word_info_t info = {.start = -1, .word_idx = 0, .words = malloc(sizeof(char *) * 3)};

    int ret = handle_special_token(line, &i, &info);

    cr_assert_eq(ret, 84);
    free(info.words);
}
