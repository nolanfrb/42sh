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
    int i;
} command_info_t;

typedef struct path_search_s {
    char *command;
    char *result_path;
    shell_t *shell;
} path_search_t;

typedef struct builtin_s {
    char *name;
    int (*func)(shell_t *, char **);
} builtin_t;

typedef struct {
    int prev[2];
    int curr[2];
} pipe_state_t;

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
int execute_builtin(ast_node_t *node, struct shell_s *shell_var);
int execute_subshell_command(ast_node_t *ast, shell_t *shell_var);

char *build_path(shell_t *shell, char *command);
char *my_strcat(char *dest, char const *str);

// Function prototypes for builtins
const builtin_t *get_builtins(void);

// Function prototypes for pipes
ast_node_t **collect_pipe_commands(ast_node_t *node, int *count);
int initialize_command_info(command_info_t *command_info,
    ast_node_t *node);
int setup_pipes_and_fork(command_info_t *info, shell_t *shell);
int create_pipe_if_needed(int curr_pipe[2], int prev_pipe[2], int i,
    int command_count);
void setup_child_pipes(int prev_pipe[2], int curr_pipe[2]);
int process_pipe_command(command_info_t *info, int idx,
    shell_t *shell, pipe_state_t *state);
void close_parent_pipes(int prev_pipe[2]);
void setup_pipes(pipe_state_t *state, int idx, int count);
#endif
