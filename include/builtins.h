/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtins
*/

#ifndef INCLUDED_BUILTINS_H
    #define INCLUDED_BUILTINS_H
    #define INITIAL_HISTORY_CAPACITY 32

struct shell_s;
typedef struct shell_s shell_t;
struct history_s;
typedef struct history_s history_t;

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
history_t *init_history(void);
void history_add(history_t *hist, const char *line);
char *history_resolve(history_t *hist, const char *input);
int builtin_history(shell_t *shell, char **args);
int handle_history_error(const char *input);
int builtin_set(shell_t *shell, char **args);
void set_local_value(shell_t *shell, const char *var, const char *value);

#endif
