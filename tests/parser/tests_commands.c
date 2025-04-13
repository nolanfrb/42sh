/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** tests_commands
*/

#include <criterion/criterion.h>
#include "ast.h"


Test(parse_command, basic_command_single_token) {
    char *tokens[] = {"ls", NULL};
    int pos = 0;

    ast_node_t *node = parse_command(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_COMMAND);
    cr_assert_not_null(node->data.command);
    cr_assert_str_eq(node->data.command->argv[0], "ls");
    cr_assert_null(node->data.command->argv[1]);
    cr_assert_eq(pos, 1);

    free_ast(node);
}

Test(parse_command, command_with_multiple_args) {
    char *tokens[] = {"gcc", "-o", "main", "main.c", NULL};
    int pos = 0;

    ast_node_t *node = parse_command(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_COMMAND);
    cr_assert_str_eq(node->data.command->argv[0], "gcc");
    cr_assert_str_eq(node->data.command->argv[1], "-o");
    cr_assert_str_eq(node->data.command->argv[2], "main");
    cr_assert_str_eq(node->data.command->argv[3], "main.c");
    cr_assert_null(node->data.command->argv[4]);
    cr_assert_eq(pos, 4);

    free_ast(node);
}

Test(parse_command, command_with_operator_stopping) {
    char *tokens[] = {"echo", "hello", "|", "grep", NULL};
    int pos = 0;

    ast_node_t *node = parse_command(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_COMMAND);
    cr_assert_str_eq(node->data.command->argv[0], "echo");
    cr_assert_str_eq(node->data.command->argv[1], "hello");
    cr_assert_null(node->data.command->argv[2]);
    cr_assert_eq(pos, 2); // stopped at '|'

    free_ast(node);
}

Test(parse_command, empty_tokens_array_should_return_null) {
    char *tokens[] = {NULL};
    int pos = 0;

    ast_node_t *node = parse_command(tokens, &pos);
    cr_assert_null(node);
}

Test(parse_command, first_token_is_special_op_should_return_null) {
    char *tokens[] = {"|", "ls", NULL};
    int pos = 0;

    ast_node_t *node = parse_command(tokens, &pos);
    cr_assert_null(node);
}

Test(parse_command, command_with_trailing_special_op_does_not_consume_it) {
    char *tokens[] = {"cat", "file.txt", ">", "output.txt", NULL};
    int pos = 0;

    ast_node_t *node = parse_command(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_str_eq(node->data.command->argv[0], "cat");
    cr_assert_str_eq(node->data.command->argv[1], "file.txt");
    cr_assert_null(node->data.command->argv[2]);
    cr_assert_eq(pos, 2); // Must stop before '>' operator

    free_ast(node);
}

Test(parse_command, command_returns_null_on_arg_count_zero) {
    char *tokens[] = {"&&", NULL};
    int pos = 0;

    ast_node_t *node = parse_command(tokens, &pos);
    cr_assert_null(node);
}