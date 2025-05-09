/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_command_path
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "command.h"
#include "env.h"
#include "utils.h"

/**
 * @brief Expand tilde (~) in path to home directory
 * @param path Path that may contain tilde
 * @return Newly allocated string with expanded path or NULL
 */
static char *expand_tilde(const char *path)
{
    char *expanded_path = NULL;
    char *tmp = NULL;
    const char *home = getenv("HOME");

    if (!home || path[0] != '~')
        return strdup(path);
    expanded_path = strdup(home);
    if (!expanded_path)
        return NULL;
    tmp = my_strcat(expanded_path, path + 1);
    free(expanded_path);
    return tmp;
}

/**
 * @brief Build a full path by combining directory and command
 * @param dir Directory path
 * @param command Command name
 * @return Newly allocated full path or NULL
 */
static char *build_full_path(char *dir, char *command)
{
    char *path_with_slash = NULL;
    char *full_path = NULL;

    path_with_slash = my_strcat(dir, "/");
    if (!path_with_slash)
        return NULL;
    full_path = my_strcat(path_with_slash, command);
    free(path_with_slash);
    return full_path;
}

/**
 * @brief Check if path is accessible and update search structure
 * @param path Path to check
 * @param search Search structure to update
 * @return 0 if path exists and is accessible, 1 otherwise
 */
static int check_path_access(char *path, path_search_t *search)
{
    if (access(path, F_OK) == 0) {
        search->result_path = path;
        return 0;
    }
    return 1;
}

/**
 * @brief Process a single PATH directory token
 * @param token Directory from PATH
 * @param search Search structure
 * @return 0 if command found, 1 otherwise
 */
static int process_path_token(char *token, path_search_t *search)
{
    char *expanded_dir = NULL;
    char *full_path = NULL;
    int result;

    expanded_dir = expand_tilde(token);
    if (!expanded_dir)
        return 1;
    full_path = build_full_path(expanded_dir, search->command);
    free(expanded_dir);
    if (!full_path)
        return 1;
    result = check_path_access(full_path, search);
    if (result != 0)
        free(full_path);
    return result;
}

/**
 * @brief Check command in all PATH directories
 * @param path_str PATH environment variable
 * @param search Search structure
 * @return 0 if command found, 1 otherwise
 */
static int check_command_in_path(char *path_str, path_search_t *search)
{
    char *path_copy = strdup(path_str);
    char *token = NULL;
    int result = 1;

    if (!path_copy)
        return 1;
    token = strtok(path_copy, ":");
    while (token) {
        if (process_path_token(token, search) == 0) {
            result = 0;
            break;
        }
        token = strtok(NULL, ":");
    }
    free(path_copy);
    return result;
}

/**
 * @brief Search for command in PATH
 * @param shell Shell context
 * @param command Command to search for
 * @return 0 if command found, 1 otherwise
 */
char *build_path(shell_t *shell, char *command)
{
    char *path = get_path(shell->env_array);
    path_search_t search = {0};
    int result;

    if (strrchr(command, '/') != NULL)
        return command;
    search.command = command;
    search.shell = shell;
    search.result_path = NULL;
    result = check_command_in_path(path, &search);
    if (result == 0)
        return search.result_path;
    return command;
}
