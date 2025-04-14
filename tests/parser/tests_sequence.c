/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** tests_sequence
*/

#include <criterion/criterion.h>
#include "ast.h"

Test(parse_sequence, simple_sequence_two_commands)
{
    char *tokens[] = {"echo", ";", "ls", NULL};
    int pos = 0;

    ast_node_t *node = parse_sequence(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_SEQUENCE);
    cr_assert_str_eq(node->data.binop.left->data.command->argv[0], "echo");
    cr_assert_str_eq(node->data.binop.right->data.command->argv[0], "ls");

    cr_assert_eq(pos, 3);
    free_ast(node);
}

Test(parse_sequence, multiple_sequenced_commands)
{
    char *tokens[] = {"a", ";", "b", ";", "c", NULL};
    int pos = 0;

    ast_node_t *node = parse_sequence(tokens, &pos);
    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_SEQUENCE);
    cr_assert_str_eq(node->data.binop.right->data.command->argv[0], "c");
    cr_assert_eq(pos, 5);

    free_ast(node);
}

Test(parse_sequence, no_sequence_operator_returns_single_command)
{
    char *tokens[] = {"ls", NULL};
    int pos = 0;

    ast_node_t *node = parse_sequence(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_COMMAND);
    cr_assert_str_eq(node->data.command->argv[0], "ls");
    cr_assert_eq(pos, 1);

    free_ast(node);
}

Test(parse_sequence, semicolon_with_missing_command_should_return_null)
{
    char *tokens[] = {"ls", ";", NULL};
    int pos = 0;

    ast_node_t *node = parse_sequence(tokens, &pos);
    cr_assert_null(node->data.binop.right);
}

Test(parse_sequence, only_semicolon_should_fail)
{
    char *tokens[] = {";", NULL};
    int pos = 0;

    ast_node_t *node = parse_sequence(tokens, &pos);
    cr_assert_null(node->data.binop.left);
    cr_assert_null(node->data.binop.right);
}
