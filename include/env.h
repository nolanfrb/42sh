/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** env
*/

#ifndef INCLUDED_ENV_H
    #define INCLUDED_ENV_H
    #include "shell.h"

void free_shell(shell_t *shell);
char *get_env_value(shell_t *shell, const char *var);
shell_t *init_shell(char **env);
void set_env_value(shell_t *shell, const char *var, const char *value);
void unset_env_value(shell_t *shell, const char *var);



#endif
