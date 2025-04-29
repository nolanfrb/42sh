/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_user_input
*/

#include "shell.h"
#include "ast.h"
#include "lexer.h"
#include "builtins.h"
#include "line_editing.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *handle_history_expansion(
    shell_t *shell, char *line, bool *had_error)
{
    char *resolved = history_resolve(shell->history, line);

    if (!resolved) {
        handle_history_error(line);
        shell->exit_code = 1;
        *had_error = true;
        free(line);
        return NULL;
    }
    free(line);
    line = strdup(resolved);
    if (!line) {
        *had_error = true;
        return NULL;
    }
    printf("%s\n", line);
    return line;
}

char *read_command(shell_t *shell, bool *had_error)
{
    char *line = NULL;

    line = read_command_line(shell, had_error);
    if (!line)
        return NULL;
    if (shell && shell->history && line[0] == '!') {
        line = handle_history_expansion(shell, line, had_error);
        if (!line)
            return NULL;
    }
    if (shell && shell->history && line[0] != '\0')
        history_add(shell->history, line);
    return line;
}

ast_node_t *built_ast_struct(char *user_input)
{
    char **tokens;
    ast_node_t *ast;
    int pos = 0;

    tokens = lexer(user_input);
    if (user_input_error_handling(tokens) != 0)
        return NULL;
    if (!tokens) {
        fprintf(stderr, "Lexer failed\n");
        return NULL;
    }
    ast = parse_sequence(tokens, &pos);
    if (ast_error_handling(ast) != 0)
        return NULL;
    if (!ast)
        return NULL;
    return ast;
}
