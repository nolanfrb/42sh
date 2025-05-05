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
#include "line_editing.h"
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
    if (!shell->alias)
        return 1;
    save_terminal_settings();
    set_non_canonical_mode();
    main_loop(shell);
    exit_code = shell->exit_code;
    free_shell(shell);
    restore_terminal_settings();
    return exit_code;
}
