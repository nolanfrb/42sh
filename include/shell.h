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
typedef int (*command_func_t)(shell_t *);

typedef enum redirection_type_e {
    REDIR_NONE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    REDIR_HEREDOC
} redirection_type_t;

typedef enum node_type_e {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_REDIRECT,
    NODE_SEQUENCE,
    NODE_AND,
    NODE_OR
} node_type_t;

typedef struct ast_node_s {
    node_type_t type;
    ast_node_t *left;
    ast_node_t *right;
    char **argv;
    char *filename;
} ast_node_t;

void (*execute_functions[])(ast_node_t*) = {
    [NODE_COMMAND] = execute_command,
    [NODE_PIPE] = execute_pipe,
    [NODE_REDIRECT] = execute_redirect,
    [NODE_SEQUENCE] = execute_sequence,
    [NODE_AND] = execute_and,
    [NODE_OR] = execute_or
};

typedef struct command_s {
    char **av;
    int ac;
    bool is_builtin;
} command_t;

typedef struct redirection_s {
    redirection_type_t type;
    char *filename;
    int fd;
} redirection_t;

struct shell_s {
    char **env;
    char **local_vars;
};

#endif /* !SHELL_H_ */
