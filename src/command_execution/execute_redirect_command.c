/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_redirect_command
*/

#include "ast.h"
#include "command.h"
#include "redirect_cmd.h"
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include "string.h"
#include <stdio.h>


void handle_output_redirection(char *filepath)
{
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void handle_append_redirection(char *filepath)
{
    int fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void handle_input_redirection(char *filepath)
{
    int fd = open(filepath, O_RDONLY);

    if (fd == -1) {
        exit(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void handle_heredoc_redirection(char *delimiter)
{
    int pipefd[2];
    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, stdin);

    if (pipe(pipefd) == -1)
        exit(1);
    while (read != -1) {
        if (read > 0 && line[read - 1] == '\n')
            line[read - 1] = '\0';
        if (strcmp(line, delimiter) == 0)
            break;
        write(pipefd[1], line, strlen(line));
        write(pipefd[1], "\n", 1);
        read = getline(&line, &len, stdin);
    }
    free(line);
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
}

int execute_redirect(ast_node_t *node, struct shell_s *shell_info)
{
    pid_t pid = fork();
    int status;
    void (*handler)(char *) = get_redirect_handler(node->data.redir.type);

    if (handler == NULL) {
        fprintf(stderr, "error: invalid redirection type\n");
        return 1;
    }
    if (pid == -1) {
        return 1;
    } else if (pid == 0) {
        handler(node->data.redir.filename);
        exit(process_command(node->data.redir.child, shell_info));
    } else {
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}
