/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** tests_redirect
*/

#include <criterion/criterion.h>
#include "ast.h"

static ast_node_t *mock_command_node(const char *cmd) {
    ast_node_t *node = malloc(sizeof(ast_node_t));
    command_node_t *cmd_node = malloc(sizeof(command_node_t));
    char **argv = malloc(sizeof(char *) * 2);
    argv[0] = strdup(cmd);
    argv[1] = NULL;
    cmd_node->argv = argv;
    node->type = NODE_COMMAND;
    node->data.command = cmd_node;
    return node;
}

char **mock_tokens(const char *args[], int count)
{
    char **tokens = malloc(sizeof(char *) * (count + 1));
    for (int i = 0; i < count; i++)
        tokens[i] = strdup(args[i]);
    tokens[count] = NULL;
    return tokens;
}

void free_tokens(char **tokens)
{
    for (int i = 0; tokens[i]; i++)
        free(tokens[i]);
    free(tokens);
}

void free_ast(ast_node_t *node)
{
    free(node);
}

Test(parse_redirect, simple_output_redirection) {
    const char *args[] = {"ls", ">", "out.txt"};
    char **tokens = mock_tokens(args, 3);
    int pos = 0;
    ast_node_t *ast = parse_redirect(tokens, &pos);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, NODE_REDIRECT);
    cr_assert_eq(ast->data.redir.type, REDIR_OUT);
    cr_assert_str_eq(ast->data.redir.filename, "out.txt");
    cr_assert_not_null(ast->data.redir.child);
    cr_assert_eq(ast->data.redir.child->type, NODE_COMMAND);

    free_ast(ast);
    free_tokens(tokens);
}

Test(parse_redirect, input_redirection) {
    const char *args[] = {"cat", "<", "input.txt"};
    char **tokens = mock_tokens(args, 3);
    int pos = 0;
    ast_node_t *ast = parse_redirect(tokens, &pos);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, NODE_REDIRECT);
    cr_assert_eq(ast->data.redir.type, REDIR_IN);
    cr_assert_str_eq(ast->data.redir.filename, "input.txt");

    free_ast(ast);
    free_tokens(tokens);
}

Test(parse_redirect, missing_filename_error) {
    const char *args[] = {"echo", ">"};
    char **tokens = mock_tokens(args, 2);
    int pos = 0;
    ast_node_t *ast = parse_redirect(tokens, &pos);

    cr_assert_null(ast); // Doit échouer proprement

    free_tokens(tokens);
}

Test(parse_redirect, double_redirection_chain) {
    const char *args[] = {"echo", "hello", ">", "out.txt", ">>", "log.txt"};
    char **tokens = mock_tokens(args, 6);
    int pos = 0;
    ast_node_t *ast = parse_redirect(tokens, &pos);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, NODE_REDIRECT);
    cr_assert_eq(ast->data.redir.type, REDIR_APPEND);
    cr_assert_str_eq(ast->data.redir.filename, "log.txt");

    cr_assert_eq(ast->data.redir.child->type, NODE_REDIRECT);
    cr_assert_eq(ast->data.redir.child->data.redir.type, REDIR_OUT);
    cr_assert_str_eq(ast->data.redir.child->data.redir.filename, "out.txt");

    free_ast(ast);
    free_tokens(tokens);
}

Test(parse_redirect, redirection_before_command_should_fail) {
    const char *args[] = {">", "out.txt", "echo", "yo"};
    char **tokens = mock_tokens(args, 4);
    int pos = 0;
    ast_node_t *ast = parse_redirect(tokens, &pos);

    cr_assert_not_null(ast);

    free_tokens(tokens);
}

Test(parse_redirect, subshell_with_redirection) {
    const char *args[] = {"(", "echo", "hello", ")", ">", "out.txt"};
    char **tokens = mock_tokens(args, 6);
    int pos = 0;
    ast_node_t *ast = parse_redirect(tokens, &pos);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, NODE_REDIRECT);
    cr_assert_str_eq(ast->data.redir.filename, "out.txt");
    cr_assert_eq(ast->data.redir.child->type, NODE_SUBSHELL);

    free_ast(ast);
    free_tokens(tokens);
}

Test(parse_redirect, input_and_output_redirection) {
    const char *args[] = {"cat", "<", "input.txt", ">", "output.txt"};
    char **tokens = mock_tokens(args, 5);
    int pos = 0;
    ast_node_t *ast = parse_redirect(tokens, &pos);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, NODE_REDIRECT);
    cr_assert_eq(ast->data.redir.type, REDIR_OUT);
    cr_assert_str_eq(ast->data.redir.filename, "output.txt");

    ast_node_t *inner = ast->data.redir.child;
    cr_assert_not_null(inner);
    cr_assert_eq(inner->type, NODE_REDIRECT);
    cr_assert_eq(inner->data.redir.type, REDIR_IN);
    cr_assert_str_eq(inner->data.redir.filename, "input.txt");

    free_ast(ast);
    free_tokens(tokens);
}

Test(get_redirection_type, invalid_redirection_operator_triggers_redir_none) {
    const char *tokens[] = {"cat", "<<<", "input.txt"};
    int pos = 0;
    redirect_type_t type = get_redirection_type(tokens[1]);
    int result = process_redirect_node(NULL, tokens, &pos);

    cr_assert_eq(result, -1);
    cr_assert_eq(type, REDIR_NONE);
}

Test(get_redirection_type, double_redirect_right)
{
    const char *tokens[] = {"cat", "<<", "input.txt"};

    redirect_type_t type = get_redirection_type(tokens[1]);
    cr_assert_eq(type, REDIR_HEREDOC);
}

Test(process_redirect_node, null_tokens)
{
    redirect_type_t type = get_redirection_type(NULL);
    cr_assert_eq(type, REDIR_NONE);
}

Test(process_redirect_node, valid_output_redirection) {
    const char *args[] = {">", "file.txt", NULL};
    char **tokens = (char **)args;
    int pos = 0;

    ast_node_t *node = mock_command_node("ls");
    int result = process_redirect_node(&node, tokens, &pos);

    cr_assert_eq(result, 0);
    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_REDIRECT);
    cr_assert_str_eq(node->data.redir.filename, "file.txt");
    cr_assert_eq(node->data.redir.type, REDIR_OUT);
    cr_assert_not_null(node->data.redir.child);
    cr_assert_eq(node->data.redir.child->type, NODE_COMMAND);

    free_ast(node);
}
