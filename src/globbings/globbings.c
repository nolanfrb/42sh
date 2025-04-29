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
    if (strchr(pattern, '*') != NULL || strchr(pattern, '?') != NULL ||
    strchr(pattern, '[') != NULL || strchr(pattern, '{') != NULL)
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
            selected_files = realloc(selected_files, sizeof(char *) *
            (count + 1));
            selected_files[count - 1] = strdup(files[i]);
        }
    }
    if (selected_files != NULL)
        selected_files[count] = NULL;
    return selected_files;
}

static char *get_pattern(char *src)
{
    char *pattern;
    char *new_pattern;

    if (src == NULL)
        return NULL;
    pattern = strdup(src);
    if (strchr(pattern, '/')) {
        while (*pattern != '*' && *pattern != '\0') {
            pattern++;
        }
    }
    new_pattern = strdup(pattern);
    if (new_pattern == NULL)
        return NULL;
    return new_pattern;
}

static int get_arg_count(ast_node_t *node)
{
    int count = 0;

    while (node->data.command->argv[count] != NULL)
        count++;
    return count;
}

static char **create_new_argv(ast_node_t *node, int arg_idx, char **matches,
    int match_count)
{
    int arg_count = get_arg_count(node);
    char **new_argv = NULL;
    int i = 0;

    new_argv = malloc(sizeof(char *) * (arg_count - 1 + match_count + 1));
    if (!new_argv)
        return NULL;
    for (i = 0; i < arg_idx; i++)
        new_argv[i] = node->data.command->argv[i];
    for (int j = 0; j < match_count; j++) {
        new_argv[i] = strdup(matches[j]);
        i++;
    }
    for (int j = arg_idx + 1; j < arg_count; j++) {
        new_argv[i] = node->data.command->argv[j];
        i++;
    }
    new_argv[i] = NULL;
    return new_argv;
}

static void replace_arg_with_matches(ast_node_t *node, int arg_idx,
    char **matches, int match_count)
{
    char **new_argv = NULL;

    new_argv = create_new_argv(node, arg_idx, matches, match_count);
    if (!new_argv)
        return;
    free(node->data.command->argv[arg_idx]);
    free(node->data.command->argv);
    node->data.command->argv = new_argv;
}

static void handle_selected_files(ast_node_t *node, int i,
    char **selected_file, int selected_count)
{
    if (selected_count > 0) {
        replace_arg_with_matches(node, i, selected_file, selected_count);
    } else {
        free(node->data.command->argv[i]);
        node->data.command->argv[i] = strdup(node->data.command->argv[i]);
    }
}

static void put_globbings(ast_node_t *node, int i)
{
    int count = 0;
    char **files = NULL;
    char **selected_file = NULL;
    char *pattern = get_pattern(node->data.command->argv[i]);
    int selected_count = 0;

    if (node->data.command->argv[i][0] == '*')
        node->data.command->argv[i][0] = '.';
    if (node->data.command->argv[i][strlen(node->data.command->argv[i]) - 1]
    == '*' || node->data.command->argv[i][0] == '.')
        files = get_directory(node->data.command->argv[i], &count);
    else
        files = get_files(node->data.command->argv[i], &count);
    selected_file = get_selected_files(files, pattern, count);
    if (selected_file != NULL) {
        while (selected_file[selected_count] != NULL)
            selected_count++;
    }
    handle_selected_files(node, i, selected_file, selected_count);
}

void globbings(ast_node_t *node)
{
    if (!node || !node->data.command || !node->data.command->argv) {
        return;
    }
    if (node->type != NODE_COMMAND) {
        return;
    }
    for (int i = 1; node->data.command->argv[i] != NULL; i++) {
        if (is_globbings_pattern(node->data.command->argv[i]) == 0)
            continue;
        put_globbings(node, i);
    }
}
