/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_globbings_getdirectory
*/

#include <criterion/criterion.h>
#include <criterion/hooks.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "globbings.h"

Test(get_directory, wrong_directory)
{
    int count = 0;
    char **files = get_directory("hsdf", &count);

    cr_assert_null(files);
    cr_assert_eq(count, 0);
}

Test(get_directory, simple_directory)
{
    int count = 0;
    char **files = get_directory("src/", &count);

    cr_assert_not_null(files);
    cr_assert_eq(count, 10);
    free(files);
}

Test(get_directory, directory_without_trailing_slash)
{
    int count = 0;
    char **files = get_directory("src", &count);

    cr_assert_not_null(files);
    cr_assert_eq(count, 10);
    free(files);
}