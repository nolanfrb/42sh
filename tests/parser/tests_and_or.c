/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** tests_and_or
*/

#include <criterion/criterion.h>
#include "ast.h"

Test(parse_and_or, simple_and_operation)
{
    char *tokens[] = {"echo", "&&", "ls", NULL};
    int pos = 0;

    ast_node_t *node = parse_and_or(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_AND);
    cr_assert_str_eq(node->data.binop.left->data.command->argv[0], "echo");
    cr_assert_str_eq(node->data.binop.right->data.command->argv[0], "ls");
    cr_assert_eq(pos, 3);

    free_ast(node);
}

Test(parse_and_or, simple_or_operation)
{
    char *tokens[] = {"cmd1", "||", "cmd2", NULL};
    int pos = 0;

    ast_node_t *node = parse_and_or(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_OR);
    cr_assert_str_eq(node->data.binop.left->data.command->argv[0], "cmd1");
    cr_assert_str_eq(node->data.binop.right->data.command->argv[0], "cmd2");

    free_ast(node);
}

Test(parse_and_or, chained_and_or)
{
    char *tokens[] = {"a", "&&", "b", "||", "c", NULL};
    int pos = 0;

    ast_node_t *node = parse_and_or(tokens, &pos);

    // ((a && b) || c)
    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_OR);

    ast_node_t *left = node->data.binop.left;
    ast_node_t *right = node->data.binop.right;

    cr_assert_eq(left->type, NODE_AND);
    cr_assert_str_eq(left->data.binop.left->data.command->argv[0], "a");
    cr_assert_str_eq(left->data.binop.right->data.command->argv[0], "b");

    cr_assert_str_eq(right->data.command->argv[0], "c");

    free_ast(node);
}

Test(parse_and_or, command_without_operator_should_return_single_node)
{
    char *tokens[] = {"echo", NULL};
    int pos = 0;

    ast_node_t *node = parse_and_or(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_COMMAND);
    cr_assert_str_eq(node->data.command->argv[0], "echo");
    cr_assert_eq(pos, 1);

    free_ast(node);
}

Test(parse_and_or, operator_with_missing_right_side_should_return_null)
{
    char *tokens[] = {"echo", "&&", NULL};
    int pos = 0;

    ast_node_t *node = parse_and_or(tokens, &pos);

    cr_assert_null(node);
}
