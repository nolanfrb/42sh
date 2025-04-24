/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** main
*/

#include "shell.h"
#include "ast.h"
#include "env.h"
#include "lexer.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static void display_prompt(void)
{
    write(STDOUT_FILENO, "$>", 2);
}

static void main_loop(shell_t *shell_info)
{
    int is_interactive = isatty(STDIN_FILENO);
    ast_node_t *ast;
    char *user_input;
    bool had_error = false;

    while (1) {
        had_error = false;
        if (is_interactive)
            display_prompt();
        user_input = read_command(shell_info, &had_error);
        if (user_input == NULL && !had_error)
            break;
        if (user_input && user_input[0] != '\0') {
            ast = built_ast_struct(user_input);
            process_command(ast, shell_info);
        }
        free(user_input);
    }
}

int main(int argc, char **argv, char **env)
{
    shell_t *shell = init_shell(env);
    int exit_code;

    (void)argc;
    (void)argv;
    main_loop(shell);
    exit_code = shell->exit_code;
    free_shell(shell);
    return exit_code;
}
