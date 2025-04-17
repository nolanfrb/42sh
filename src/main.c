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

    while (1) {
        if (is_interactive)
            display_prompt();
        user_input = read_command();
        if (user_input == NULL)
            break;
        if (user_input[0] != '\n') {
            ast = built_ast_struct(user_input);
            process_command(ast, shell_info);
            free(user_input);
        }
    }
}

int main(int argc, char **argv, char **env)
{
    shell_t *shell = init_shell(env);

    main_loop(shell);
    return 0;
}
