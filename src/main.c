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
#include "alias.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>



static void display_prompt(void)
{
    write(STDOUT_FILENO, "$>", 2);
}

void handle_user_input(shell_t *shell_info, char *user_input)
{
    ast_node_t *ast;

    if (user_input && user_input[0] != '\n') {
        ast = built_ast_struct(user_input, shell_info);
        if (ast == NULL) {
            free(user_input);
            return;
        }
        process_command(ast, shell_info);
        free(user_input);
    }
}

static void main_loop(shell_t *shell_info)
{
    int is_interactive = isatty(STDIN_FILENO);
    char *user_input;
    bool had_error = false;

    while (1) {
        had_error = false;
        if (is_interactive)
            display_prompt();
        user_input = read_command(shell_info, &had_error);
        if (user_input == NULL && !had_error)
            break;
        handle_user_input(shell_info, user_input);
    }
}

int main(int argc, char **argv, char **env)
{
    shell_t *shell = init_shell(env);
    int exit_code;

    (void)argc;
    (void)argv;
    shell->alias = load_alias();
    main_loop(shell);
    exit_code = shell->exit_code;
    free_shell(shell);
    return exit_code;
}
