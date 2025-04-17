/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** command
*/

#ifndef INCLUDED_COMMAND_H
    #define INCLUDED_COMMAND_H
    #include "shell.h"
    #include "ast.h"
    #include <sys/types.h>

typedef enum redirect_type_e redirect_type_t;

typedef struct command_info_s {
    int command_count;
    ast_node_t **commands;
    pid_t *pids;
    int (*pipes)[2];
} command_info_t;

typedef struct path_search_s {
    char *command;
    char *result_path;
    shell_t *shell;
} path_search_t;

// Utility functions
void handle_command_not_found(char *command);
void handle_exit_status(int status);
bool is_builtin_cmd(ast_node_t *node);
// Function prototypes for execution
int execute_command(ast_node_t *node, struct shell_s *shell_var);
int execute_pipe(ast_node_t *node, struct shell_s *shell_var);
int execute_or(ast_node_t *ast, shell_t *shell_info);
int execute_and(ast_node_t *ast, shell_t *shell_info);
int execute_sequence(ast_node_t *ast, shell_t *shell_info);
int execute_redirect(ast_node_t *node, struct shell_s *shell_var);
void (*get_redirect_handler(redirect_type_t type))(char *);

char *build_path(shell_t *shell, char *command);
char *my_strcat(char *dest, char const *str);

#endif
