/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** shell
*/

#ifndef SHELL_H_
    #define SHELL_H_
    #define DEFAULT_PATH "/bin:/usr/bin:/usr/local/bin:/sbin:/usr/sbin"
    #include <stdbool.h>

typedef struct shell_s shell_t;
typedef struct ast_node_s ast_node_t;

typedef struct command_s {
    char **av;
    int ac;
    bool is_builtin;
} command_t;

// typedef struct redirection_s {
//     redirection_type_t type;
//     char *filename;
//     int fd;
// } redirection_t;

struct shell_s {
    char **env_array;
    int env_size;
    char **local_vars;
    int local_size;
    int exit_code;
};

ast_node_t *built_ast_struct(char *user_input);
int process_command(ast_node_t *ast, shell_t *shell_info);
char *read_command(void);
int builtin_env(shell_t *shell, char **args);
int builtin_setenv(shell_t *shell, char **args);
int builtin_unsetenv(shell_t *shell, char **args);
int builtin_echo(shell_t *shell, char **args);
int is_double_quoted(char *str);
int is_single_quoted(char *str);
void print_env_variable(shell_t *shell, char *var);
void handle_double_quotes(shell_t *shell, char *arg);
void print_single_quoted(char *arg);
#endif /* !SHELL_H_ */
