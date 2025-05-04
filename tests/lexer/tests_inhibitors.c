/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** tests_inhibitors
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "src/lexer/handle_inhibitors.c"

Test(inhibitors, is_inhibitor)
{
    cr_assert_eq(is_inhibitor('"'), true);
    cr_assert_eq(is_inhibitor('\''), true);
    cr_assert_eq(is_inhibitor('\\'), true);
    cr_assert_eq(is_inhibitor('`'), true);
    cr_assert_eq(is_inhibitor('a'), false);
}

Test(inhibitors, find_inhibitor_end)
{
    char *cmd_line = "echo \"Hello World\"";
    int start = 5;
    int end = find_inhibitor_end(cmd_line, start, '"');

    cr_assert_eq(end, 17);
}

Test(inhibitors, find_inhibitor_end_no_match)
{
    char *cmd_line = "echo \"Hello World\"";
    int start = 5;
    int end = find_inhibitor_end(cmd_line, start, '\'');

    cr_assert_eq(end, -1);
}

Test(inhibitors, find_inhibitor_end_backslash)
{
    char *cmd_line = "echo \\Hello World";
    int start = 5;
    int end = find_inhibitor_end(cmd_line, start, '\\');

    cr_assert_eq(end, 7);
}

Test(inhibitors, extract_inhibited_content)
{
    char *cmd_line = "echo \"Hello World\"";
    int start = 5;
    int end = 17;
    char *content = extract_inhibited_content(cmd_line, start, end);

    cr_assert_str_eq(content, "Hello World");
    free(content);
}

Test(inhibitors, process_inhibitor)
{
    char *cmd_line = "echo \"Hello World\"";
    int pos = 5;
    char *combined = NULL;

    int result = process_inhibitor(cmd_line, &pos, &combined);

    cr_assert_eq(result, 0);
    cr_assert_str_eq(combined, "Hello World");
    free(combined);
}