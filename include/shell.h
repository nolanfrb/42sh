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
    char **env;
    char **local_vars;
    int exit_code;
};

#endif /* !SHELL_H_ */
