/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** command
*/

#ifndef INCLUDED_COMMAND_H
    #define INCLUDED_COMMAND_H

void handle_command_not_found(char *command);
void handle_exit_status(int status);
// Function prototypes for execution
int execute_command(ast_node_t *node, struct shell_s *shell_var);

#endif
