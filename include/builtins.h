/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtins
*/

#ifndef INCLUDED_BUILTINS_H
    #define INCLUDED_BUILTINS_H
    #include "shell.h"

int builtin_env(shell_t *shell, char **args);
int builtin_setenv(shell_t *shell, char **args);
int builtin_unsetenv(shell_t *shell, char **args);
int builtin_echo(shell_t *shell, char **args);
int is_double_quoted(char *str);
int is_single_quoted(char *str);
void print_env_variable(shell_t *shell, char *var);
void handle_double_quotes(shell_t *shell, char *arg);
void print_single_quoted(char *arg);
int builtin_cd(shell_t *shell, char **args);
int builtin_exit(shell_t *shell, char **args);


#endif
