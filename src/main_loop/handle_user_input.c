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
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *resolve_history_event(shell_t *shell, char *line)
{
    char *resolved = NULL;

    if (!shell || !shell->history || !line)
        return line;
    resolved = history_resolve(shell->history, line);
    if (!resolved) {
        handle_history_error(line);
        free(line);
        return NULL;
    }
    free(line);
    line = strdup(resolved);
    if (!line)
        return NULL;
    printf("%s\n", line);
    return line;
}

char *read_command(shell_t *shell)
{
    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, stdin) == -1) {
        free(line);
        return NULL;
    }
    line[strcspn(line, "\n")] = '\0';
    if (line && shell && shell->history && line[0] == '!')
        line = resolve_history_event(shell, line);
    if (!line)
        return NULL;
    if (line[0] != '\0')
        history_add(shell->history, line);
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
        return NULL;
    }
    ast = parse_sequence(tokens, &pos);
    if (!ast) {
        fprintf(stderr, "Parser failed\n");
        return NULL;
    }
    return ast;
}
