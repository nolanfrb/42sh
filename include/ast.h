/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** ast
*/

#ifndef AST_H
    #define AST_H
    #include "shell.h"
    #include <stdlib.h>
    #define OPERATOR_COUNT 12

extern const char *REDIRECTION_TOKENS[];

typedef struct word_info_s word_info_t;
typedef int (*command_func_t)(shell_t *);
typedef enum node_type_e node_type_t;
typedef enum redirect_type_e redirect_type_t;
typedef struct ast_node_s ast_node_t;
typedef struct command_node_s command_node_t;
typedef struct redirect_node_s redirect_node_t;
typedef struct binary_node_s binary_node_t;
typedef struct subshell_node_s subshell_node_t;
typedef union data_u data_t;

enum redirect_type_e {
    REDIR_NONE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    REDIR_HEREDOC
};

enum node_type_e {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_REDIRECT,
    NODE_SEQUENCE,
    NODE_AND,
    NODE_OR,
    NODE_SUBSHELL,
};

struct command_node_s {
    char **argv;
};

struct subshell_node_s {
    ast_node_t *child;
};

struct redirect_node_s {
    ast_node_t *child;
    redirect_type_t type;
    char *filename;
};

struct binary_node_s {
    ast_node_t *left;
    ast_node_t *right;
};

union data_u {
    command_node_t *command;
    redirect_node_t redir;
    binary_node_t binop;
    subshell_node_t subshell;
};

struct ast_node_s {
    node_type_t type;
    data_t data;
};

// void (*execute_functions[])(ast_node_t*) = {
//     [NODE_COMMAND] = execute_command,
//     [NODE_PIPE] = execute_pipe,
//     [NODE_REDIRECT] = execute_redirect,
//     [NODE_SEQUENCE] = execute_sequence,
//     [NODE_AND] = execute_and,
//     [NODE_OR] = execute_or
// };

ast_node_t *parse_sequence(char **tokens, int *pos);
ast_node_t *parse_pipes(char **tokens, int *pos);
ast_node_t *parse_redirect(char **tokens, int *pos);
ast_node_t *parse_command(char **tokens, int *pos);
ast_node_t *parse_and_or(char **tokens, int *pos);
ast_node_t *parse_subshell(char **tokens, int *pos);

// utils
bool is_special_op(char *token);
bool is_redirect_op(char *token);

// free
void free_ast(ast_node_t *node);

#endif
