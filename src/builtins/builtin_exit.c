/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_exit
*/

#include "shell.h"
#include "env.h"
#include "command.h"
#include "line_editing.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int builtin_exit(shell_t *shell, char **args)
{
    int exit_code = 0;

    (void)shell;
    if (args[1]) {
        exit_code = atoi(args[1]);
    }
    restore_terminal_settings();
    printf_flush("exit\n");
    free_shell(shell);
    exit(exit_code);
}
