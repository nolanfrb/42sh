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

    shell->history_index = shell->history->count;
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

static bool handle_user_input_errors(char **tokens, shell_t *shell_info)
{
    if (user_input_error_handling(tokens) != 0) {
        shell_info->exit_code = 1;
        return true;
    }
    if (!tokens) {
        fprintf(stderr, "Lexer failed\n");
        return true;
    }
    return false;
}

ast_node_t *built_ast_struct(char *user_input, shell_t *shell_info)
{
    char **tokens;
    ast_node_t *ast;
    int pos = 0;

    if (!user_input || user_input[0] == '\0')
        return NULL;
    tokens = build_tokens(user_input, shell_info);
    if (handle_user_input_errors(tokens, shell_info))
        return NULL;
    ast = parse_sequence(tokens, &pos);
    if (ast_error_handling(ast) != 0) {
        shell_info->exit_code = 1;
        free(tokens);
        return NULL;
    }
    if (!ast) {
        free(tokens);
        return NULL;
    }
    return ast;
}
