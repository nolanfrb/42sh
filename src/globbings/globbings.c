/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings
*/

#include "ast.h"
#include "globbings.h"
#include <stdio.h>
#include <fnmatch.h>
#include <ftw.h>
#include <string.h>

static int is_globbings_pattern(char *pattern)
{
    if (pattern == NULL)
        return 0;
    if (strchr(pattern, '*') != NULL || strchr(pattern, '?') != NULL)
        return 1;
    return 0;
}

static char **get_selected_files(char **files, char *pattern, int count_files)
{
    char **selected_files = NULL;
    int count = 0;

    for (int i = 0; i < count_files; i++) {
        if (fnmatch(pattern, files[i], 0) == 0) {
            count++;
            selected_files = realloc(selected_files, sizeof(char *) * (count + 1));
            selected_files[count - 1] = strdup(files[i]);
        }
    }
    if (selected_files != NULL)
        selected_files[count] = NULL;
    return selected_files;
}

static char *get_pattern(char *src)
{
    if (src == NULL)
        return NULL;
    char *pattern = strdup(src);
    char *new_pattern;

    if (strchr(pattern, '/')) {
        while (*pattern != '*') {
            if (*pattern == '\0')
                return NULL;
            pattern++;
        }
    }
    new_pattern = strdup(pattern);
    if (new_pattern == NULL)
        return NULL;
    return new_pattern;
}

int globbings(ast_node_t *node)
{
    if (is_globbings_pattern(node->data.command->argv[1]) == 0)
        return 0;
    int count = 0;
    char **files = NULL;
    char **selected_file = NULL;
    char *pattern = get_pattern(node->data.command->argv[1]);

    if (node->data.command->argv[1][0] == '*') {
        node->data.command->argv[1][0] = '.';
    }
    if (node->data.command->argv[1][strlen(node->data.command->argv[1]) - 1] == '*' ||
        node->data.command->argv[1][0] == '.') {
        printf("in directory\n");
        files = get_directory(node->data.command->argv[1], &count);
    } else {
        files = get_files(node->data.command->argv[1], &count);
    }
    printf("count = %i\n", count);
    for (int i = 0; i < count; i++) {
        printf("file found : %s\n", files[i]);
    }
    selected_file = get_selected_files(files, pattern, count);
    for (int i = 0; selected_file[i] != NULL; i++) {
        printf("selected file : %s\n", selected_file[i]);
        free(selected_file[i]);
    }
    free(selected_file);
    for (int i = 0; i < count; i++) {
        free(files[i]);
    }
    free(files);
    files = NULL;
}

