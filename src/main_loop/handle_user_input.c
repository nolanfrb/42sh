/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_user_input
*/

#include "shell.h"
#include "ast.h"
#include "lexer.h"
#include <unistd.h>
#include <stdio.h>

char *read_command(void)
{
    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, stdin) == -1) {
        free(line);
        return NULL;
    }
    return line;
}

ast_node_t *built_ast_struct(char *user_input)
{
    char **tokens;
    ast_node_t *ast;
    int pos = 0;

    tokens = lexer(user_input);
    if (!tokens) {
        fprintf(stderr, "Lexer failed\n");
        exit(1);
    }
    ast = parse_sequence(tokens, &pos);
    if (!ast) {
        fprintf(stderr, "Parser failed\n");
        exit(1);
    }
    return ast;
}
