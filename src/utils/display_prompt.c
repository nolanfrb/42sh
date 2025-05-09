/*
** EPITECH PROJECT, 2025
** B-PSU-200-NAN-2-1-minishell1-lukas.renaud [WSL: Ubuntu-24.04]
** File description:
** display_prompt
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"

static char *expand_tilde(const char *path, shell_t *shell)
{
    char *expanded_path = NULL;
    size_t rest_len = 0;
    const char *home = my_getenv("HOME", shell->env_array);

    if (!home)
        return strdup(path);
    if (strncmp(path, home, strlen(home)) == 0 &&
    (path[strlen(home)] == '/' || path[strlen(home)] == '\0')) {
        rest_len = strlen(path) - strlen(home);
        expanded_path = malloc(2 + rest_len);
        if (!expanded_path)
            return strdup(path);
        strcpy(expanded_path, "~");
        strcat(expanded_path, path + strlen(home));
        return expanded_path;
    }
    return strdup(path);
}

void display_prompt(shell_t *shell)
{
    char *hostname = my_gethostname();
    char *current_dir = getcwd(NULL, 0);
    char *expanded_tilde = NULL;
    char prompt_symbol = (getuid() == 0) ? '#' : '>';

    expanded_tilde = expand_tilde(current_dir, shell);
    printf_flush("\033[4m%s\033[0m:%s%c ", hostname, expanded_tilde,
        prompt_symbol);
    free(hostname);
    free(expanded_tilde);
    free(current_dir);
}
