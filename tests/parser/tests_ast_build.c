/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** tests_ast_build
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

void cr_mock_stdin(char *input)
{
    FILE *mock_input = fmemopen(input, strlen(input), "r");
    if (mock_input == NULL) {
        perror("fmemopen");
        exit(EXIT_FAILURE);
    }
    stdin = mock_input;
}


Test(read_command, simple_input)
{
    const char *input = "ls -la\n";
    char *result;

    cr_mock_stdin((char *)input);

    result = read_command();

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "ls -la\n");

    free(result);
}

Test(read_command, eof_input)
{
    FILE *null_input = fopen("/dev/null", "r");
    cr_assert_not_null(null_input);
    FILE *old_stdin = stdin;
    stdin = null_input;

    char *result = read_command();

    cr_assert_null(result);

    stdin = old_stdin;
    fclose(null_input);
}


Test(build_ast_struct, simple_input)
{
    const char *input = "ls -la\n";
    ast_node_t *ast;

    ast = built_ast_struct((char *)input);

    cr_assert_not_null(ast);
}

Test(build_ast_struct, empty_input)
{
    const char *input = "";
    ast_node_t *ast;

    ast = built_ast_struct((char *)input);

    cr_assert_null(ast);
}

Test(build_ast_struct, invalid_input)
{
    const char *input = "ls -la | grep test\n";
    ast_node_t *ast;

    ast = built_ast_struct((char *)input);

    cr_assert_not_null(ast);
}
