/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** shell
*/

#ifndef SHELL_H_
    #define SHELL_H_
    #define DEFAULT_PATH "/bin:/usr/bin:/usr/local/bin:/sbin:/usr/sbin"
    #include <stdbool.h>
    #include "builtins.h"
    #define BUFFER_SIZE 1024

typedef struct shell_s shell_t;
typedef struct ast_node_s ast_node_t;
typedef struct history_s history_t;



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
    int history_index;
    int buffer_capacity;
    history_t *history;
};

typedef struct {
    char *command;
    char *timestamp;
} history_entry_t;

typedef struct history_s {
    history_entry_t *entries;
    int count;
    int capacity;
} history_t;

ast_node_t *built_ast_struct(char *user_input, shell_t *shell_info);
int process_command(ast_node_t *ast, shell_t *shell_info);
char *read_command(shell_t *shell, bool *had_error);
void printf_flush(const char *format, ...);
char *my_getenv(char const *name, char **env);
char *my_gethostname(void);
void display_prompt(shell_t *shell);

#endif /* !SHELL_H_ */
