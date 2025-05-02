/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** process_command
*/

#include "ast.h"
#include "command.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

static void flush_stdin(ast_node_t *ast)
{
    int c;

    if (ast->type == NODE_REDIRECT && ast->data.redir.type == REDIR_HEREDOC) {
        c = getchar();
        while (c != EOF && c != '|') {
            c = getchar();
        }
        if (c == '|')
            ungetc(c, stdin);
    }
}

int process_command(ast_node_t *ast, shell_t *shell_info)
{
    static int (*execute_functions[])(ast_node_t *, shell_t *) = {
        [NODE_COMMAND] = execute_command,
        [NODE_PIPE] = execute_pipe,
        [NODE_OR] = execute_or,
        [NODE_AND] = execute_and,
        [NODE_SEQUENCE] = execute_sequence,
        [NODE_REDIRECT] = execute_redirect,
        [NODE_SUBSHELL] = execute_subshell_command,
    };

    if (ast == NULL)
        return 0;
    shell_info->exit_code = execute_functions[ast->type](ast, shell_info);
    flush_stdin(ast);
    return shell_info->exit_code;
}
