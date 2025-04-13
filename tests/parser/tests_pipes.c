/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** tests_pipe
*/

#include <criterion/criterion.h>
#include "ast.h"

Test(parse_pipes, parse_pipes_cmd)
{
    char *tokens[] = {"echo", "hello", "|", "grep", "h", NULL};
    int pos = 0;

    ast_node_t *node = parse_pipes(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_PIPE);
    cr_assert_str_eq(node->data.binop.left->data.command->argv[0], "echo");
    cr_assert_str_eq(node->data.binop.right->data.command->argv[0], "grep");
    cr_assert_eq(pos, 5);

    free_ast(node);
}