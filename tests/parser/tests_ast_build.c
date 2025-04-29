/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Tests unitaires pour read_command et build_ast_struct
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shell.h"

// Fonction pour mocker stdin
void cr_mock_stdin(char *input) {
    FILE *mock_input = fmemopen(input, strlen(input), "r");
    if (mock_input == NULL) {
        perror("fmemopen");
        exit(EXIT_FAILURE);
    }
    stdin = mock_input;
}

Test(read_command, simple_input) {
    const char *input = "ls -la\n";
    shell_t shell = {0};
    bool had_error = false;
    char *result;

    cr_mock_stdin((char *)input);

    result = read_command(&shell, &had_error);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "ls -la");
    cr_assert_eq(had_error, false);

    free(result);
}

Test(read_command, eof_input) {
    FILE *null_input = fopen("/dev/null", "r");
    cr_assert_not_null(null_input);
    FILE *old_stdin = stdin;
    shell_t shell = {0};
    bool had_error = false;

    stdin = null_input;

    char *result = read_command(&shell, &had_error);

    cr_assert_null(result);
    cr_assert_eq(had_error, false);

    stdin = old_stdin;
    fclose(null_input);
}

Test(read_command, with_history) {
    const char *input = "ls -la\n";
    shell_t shell = {0};
    bool had_error = false;
    char *result;

    shell.history = init_history();
    cr_assert_not_null(shell.history);

    cr_mock_stdin((char *)input);

    result = read_command(&shell, &had_error);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "ls -la");
    cr_assert_eq(had_error, false);

    cr_assert_eq(shell.history->count, 1);
    cr_assert_str_eq(shell.history->entries[0].command, "ls -la");

    free(result);
    free(shell.history->entries[0].command);
    free(shell.history->entries[0].timestamp);
    free(shell.history->entries);
    free(shell.history);
}

Test(read_command, history_expansion_bang_bang) {
    shell_t shell = {0};
    bool had_error = false;
    char *result;

    shell.history = init_history();
    cr_assert_not_null(shell.history);
    history_add(shell.history, "echo hello");

    cr_mock_stdin("!!\n");

    result = read_command(&shell, &had_error);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "echo hello");
    cr_assert_eq(had_error, false);

    free(result);
    // Libérer la mémoire
    free(shell.history->entries[0].command);
    free(shell.history->entries[0].timestamp);
    free(shell.history->entries);
    free(shell.history);
}

Test(read_command, history_expansion_by_number) {
    shell_t shell = {0};
    bool had_error = false;
    char *result;

    shell.history = init_history();
    cr_assert_not_null(shell.history);
    history_add(shell.history, "ls");
    history_add(shell.history, "cd /tmp");
    history_add(shell.history, "echo test");

    cr_mock_stdin("!2\n");

    result = read_command(&shell, &had_error);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "cd /tmp");
    cr_assert_eq(had_error, false);

    free(result);
    for (int i = 0; i < shell.history->count; i++) {
        free(shell.history->entries[i].command);
        free(shell.history->entries[i].timestamp);
    }
    free(shell.history->entries);
    free(shell.history);
}

Test(read_command, history_expansion_by_prefix) {
    shell_t shell = {0};
    bool had_error = false;
    char *result;

    shell.history = init_history();
    cr_assert_not_null(shell.history);
    history_add(shell.history, "ls -la");
    history_add(shell.history, "echo test");
    history_add(shell.history, "cd /usr/bin");

    cr_mock_stdin("!ec\n");

    result = read_command(&shell, &had_error);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "echo test");
    cr_assert_eq(had_error, false);

    free(result);
    for (int i = 0; i < shell.history->count; i++) {
        free(shell.history->entries[i].command);
        free(shell.history->entries[i].timestamp);
    }
    free(shell.history->entries);
    free(shell.history);
}

Test(read_command, history_expansion_error) {
    shell_t shell = {0};
    bool had_error = false;
    char *result;

    shell.history = init_history();
    cr_assert_not_null(shell.history);

    cr_mock_stdin("!nonexistent\n");

    result = read_command(&shell, &had_error);

    cr_assert_null(result);
    cr_assert_eq(had_error, true);

    free(shell.history->entries);
    free(shell.history);
}

Test(build_ast_struct, simple_input) {
    char *input = strdup("ls -la");
    shell_t shell = {0};
    ast_node_t *ast;

    ast = built_ast_struct(input, &shell);

    cr_assert_not_null(ast);

    free(input);
}

Test(build_ast_struct, empty_input) {
    char *input = strdup("");
    shell_t shell = {0};
    ast_node_t *ast;

    ast = built_ast_struct(input, &shell);

    cr_assert_null(ast);

    free(input);
}

Test(build_ast_struct, null_input) {
    shell_t shell = {0};
    ast_node_t *ast;

    ast = built_ast_struct(NULL, &shell);

    cr_assert_null(ast);
}

Test(build_ast_struct, complex_input) {
    char *input = strdup("ls -la | grep test");
    shell_t shell = {0};
    ast_node_t *ast;

    ast = built_ast_struct(input, &shell);

    cr_assert_not_null(ast);

    free(input);
}

Test(build_ast_struct, error_handling) {
    char *input = strdup("ls -la | grep test");
    shell_t shell = {0};
    ast_node_t *ast;

    ast = built_ast_struct(input, &shell);

    if (!ast) {
        cr_assert_eq(shell.exit_code, 1);
    }

    free(input);
}