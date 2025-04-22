/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** redirect_cmd
*/

#ifndef INCLUDED_REDIRECT_CMD_H
    #define INCLUDED_REDIRECT_CMD_H

void handle_output_redirection(char *filepath);
void handle_append_redirection(char *filepath);
void handle_input_redirection(char *filepath);
void handle_heredoc_redirection(char *delimiter);

#endif
