/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** command
*/

#ifndef INCLUDED_COMMAND_H
    #define INCLUDED_COMMAND_H

typedef struct command_info_s {
    int command_count;
    ast_node_t **commands;
    pid_t **pids;
    int (*pipes)[2];
} command_info_t;

void handle_command_not_found(char *command);
void handle_exit_status(int status);
// Function prototypes for execution
int execute_command(ast_node_t *node, struct shell_s *shell_var);
int execute_pipe(ast_node_t *node, struct shell_s *shell_var);

#endif
