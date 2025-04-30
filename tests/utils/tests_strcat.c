/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** tests_strcat
*/

#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>

char *my_strcat(char *dest, char *str);

Test(my_strcat, basic_concatenation)
{
    char *result = my_strcat("Hello", " World");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "Hello World");
    free(result);
}

Test(my_strcat, concatenate_with_empty_string)
{
    char *result1 = my_strcat("Hello", "");
    cr_assert_not_null(result1);
    cr_assert_str_eq(result1, "Hello");
    free(result1);

    char *result2 = my_strcat("", "World");
    cr_assert_not_null(result2);
    cr_assert_str_eq(result2, "World");
    free(result2);
}

Test(my_strcat, concatenate_two_empty_strings)
{
    char *result = my_strcat("", "");

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "");
    free(result);
}

Test(my_strcat, returns_new_allocated_string)
{
    char *res = my_strcat("foo", "bar");
    cr_assert_neq(res, "foobar");
    cr_assert_str_eq(res, "foobar");
    free(res);
}
