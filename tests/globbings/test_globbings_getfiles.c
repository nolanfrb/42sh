/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_globbings_getfiles
*/

#include <criterion/criterion.h>
#include <criterion/hooks.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "globbings.h"

Test(get_files, null_start_path)
{
    int count = 0;
    char **files = get_files(NULL, &count);

    cr_assert_null(files);
    cr_assert_eq(count, 0);
}

Test(get_files, empty_start_path)
{
    int count = 0;
    char **files = get_files("", &count);

    cr_assert_null(files);
    cr_assert_eq(count, 0);
}

Test(get_files, no_globbing)
{
    int count = 0;
    char **files = get_files("test.txt", &count);

    cr_assert_null(files);
    cr_assert_eq(count, 0);
}

Test(get_files, single_globbing)
{
    int count = 0;
    char **files = get_files("src/", &count);

    cr_assert_not_null(files);
    cr_assert_eq(count, 1);
    cr_assert_str_eq(files[0], "src/main.c");
    free(files[0]);
    free(files);
}

