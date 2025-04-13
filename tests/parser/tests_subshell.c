/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_subshell
*/

#include <criterion/criterion.h>
#include "ast.h"


Test(parse_subshell, simple_subshell) {
    char *tokens[] = {"(", "ls", ")", NULL};
    int pos = 0;

    ast_node_t *node = parse_subshell(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_SUBSHELL);
    cr_assert_not_null(node->data.subshell.child);
    cr_assert_eq(node->data.subshell.child->type, NODE_COMMAND);
    cr_assert_str_eq(node->data.subshell.child->data.command->argv[0], "ls");

    free_ast(node);
}

Test(parse_subshell, subshell_with_sequence_simulated) {
    char *tokens[] = {"(", "echo", ")", NULL};
    int pos = 0;

    ast_node_t *node = parse_subshell(tokens, &pos);
    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_SUBSHELL);
    cr_assert_str_eq(node->data.subshell.child->data.command->argv[0], "echo");

    free_ast(node);
}

Test(parse_subshell, missing_closing_parenthesis) {
    char *tokens[] = {"(", "echo", NULL};
    int pos = 0;

    ast_node_t *node = parse_subshell(tokens, &pos);
    cr_assert_null(node); // doit échouer

    // rien à free car NULL
}

// Test(parse_subshell, empty_subshell_should_fail) {
//     char *tokens[] = {"(", ")", NULL};
//     int pos = 0;

//     ast_node_t *node = parse_subshell(tokens, &pos);
//     cr_assert_null(node);
// }

Test(parse_subshell, fallback_parse_command_when_no_parenthesis) {
    char *tokens[] = {"echo", NULL};
    int pos = 0;

    ast_node_t *node = parse_subshell(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_COMMAND);
    cr_assert_str_eq(node->data.command->argv[0], "echo");

    free_ast(node);
}

// Test(parse_subshell, unexpected_closing_parenthesis) {
//     char *tokens[] = {")", NULL};
//     int pos = 0;

//     ast_node_t *node = parse_subshell(tokens, &pos);
//     cr_assert_not_null(node);
//     cr_assert_eq(node->type, NODE_COMMAND);
//     cr_assert_str_eq(node->data.command->argv[0], ")");

//     free_ast(node);
// }

Test(parse_subshell, subshell_then_logical_op) {
    char *tokens[] = {"(", "echo", ")", "&&", "echo", NULL};
    int pos = 0;

    ast_node_t *node = parse_subshell(tokens, &pos);

    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_SUBSHELL);
    cr_assert_str_eq(node->data.subshell.child->data.command->argv[0], "echo");
    cr_assert_eq(pos, 3);

    free_ast(node);
}

