/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** handle_user_input
*/

#include <unistd.h>
#include "shell.h"

void handle_user_input(shell_t *shell_info, char *user_input)
{
    if (user_input && user_input[0] != '\n') {
        shell_info->ast = built_ast_struct(user_input, shell_info);
        if (shell_info->ast == NULL) {
            free(user_input);
            return;
        }
        process_command(shell_info->ast, shell_info);
        free(user_input);
    }
}
