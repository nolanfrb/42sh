/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings_path_join
*/

#include "globbings.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int split_path_init(const char *path, string_array_t *components)
{
    char *path_copy;

    path_copy = strdup(path);
    if (!path_copy)
        return 0;
    init_string_array(components, 10);
    if (!components->array) {
        free(path_copy);
        return 0;
    }
    return 1;
}

static int split_path_process(char *path_copy, string_array_t *components)
{
    char *token;

    token = strtok(path_copy, "/");
    while (token) {
        if (!process_token(components, token)) {
            free_string_array(components->array);
            free(path_copy);
            return 0;
        }
        token = strtok(NULL, "/");
    }
    return 1;
}

char **split_path(const char *path, int *count)
{
    char *path_copy;
    string_array_t components;

    path_copy = strdup(path);
    if (!path_copy) {
        *count = 0;
        return NULL;
    }
    if (!split_path_init(path, &components)) {
        *count = 0;
        return NULL;
    }
    if (!split_path_process(path_copy, &components)) {
        *count = 0;
        return NULL;
    }
    *count = components.count;
    free(path_copy);
    return components.array;
}

static char *join_simple_path(const char *file)
{
    return strdup(file);
}

static char *allocate_joined_path(const char *dir, const char *file,
    int with_slash)
{
    size_t dir_len;
    char *result;

    dir_len = strlen(dir);
    if (with_slash)
        result = malloc(dir_len + strlen(file) + 1);
    else
        result = malloc(dir_len + strlen(file) + 2);
    return result;
}

static char *format_joined_path(const char *dir, const char *file,
    char *result)
{
    size_t dir_len;

    dir_len = strlen(dir);
    if (dir[dir_len - 1] == '/')
        sprintf(result, "%s%s", dir, file);
    else
        sprintf(result, "%s/%s", dir, file);
    return result;
}

char *join_path(const char *dir, const char *file)
{
    char *result;
    size_t dir_len;

    dir_len = strlen(dir);
    if (dir_len == 0 || (dir_len == 1 && dir[0] == '.'))
        return join_simple_path(file);
    result = allocate_joined_path(dir, file, dir[dir_len - 1] == '/');
    if (!result)
        return NULL;
    return format_joined_path(dir, file, result);
}
