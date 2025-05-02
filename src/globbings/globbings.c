/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings
*/

#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globbings.h"
#include "ast.h"

static char **handle_no_match(const char *pattern, int *count)
{
    char **result = malloc(sizeof(char *));

    if (result == NULL)
        return NULL;
    result[0] = strdup(pattern);
    *count = 1;
    return result;
}

static char **allocate_result_array(glob_t *glob_result, int count)
{
    char **result = malloc(sizeof(char *) * count);

    if (result == NULL) {
        globfree(glob_result);
        return NULL;
    }
    for (int i = 0; i < count; i++)
        result[i] = strdup(glob_result->gl_pathv[i]);
    return result;
}

static char **select_file(const char *pattern, int *count)
{
    glob_t glob_result;
    char **result = NULL;
    int status = glob(pattern, GLOB_TILDE | GLOB_NOCHECK, NULL, &glob_result);

    *count = 0;
    if (status != 0) {
        if (status == GLOB_NOMATCH)
            result = handle_no_match(pattern, count);
        globfree(&glob_result);
        return result;
    }
    *count = glob_result.gl_pathc;
    result = allocate_result_array(&glob_result, *count);
    globfree(&glob_result);
    return result;
}

static char **update_command_args(char **argv, int arg_idx, char **new_args,
    int new_count)
{
    int old_argc = count_old_args(argv);
    update_args_data_t *data = malloc(sizeof(update_args_data_t));

    if (!data)
        return argv;
    data->new_argv = malloc(sizeof(char *) * (old_argc - 1 + new_count + 1));
    if (!data->new_argv) {
        free(data);
        return argv;
    }
    data->new_idx = 0;
    copy_args(data, argv, 0, arg_idx);
    copy_args(data, new_args, 0, new_count);
    copy_args(data, argv, arg_idx + 1, old_argc);
    data->new_argv[data->new_idx] = NULL;
    free_old_args(argv);
    return data->new_argv;
}

static char **process_glob_pattern(char **argv, int *index, ast_node_t *node)
{
    char **expanded_args;
    int expanded_count;

    expanded_args = select_file(argv[*index], &expanded_count);
    if (expanded_args && expanded_count > 0) {
        argv = update_command_args(argv, *index, expanded_args,
            expanded_count);
        node->data.command->argv = argv;
        *index = 0;
    }
    return argv;
}

static void apply_globbing_to_command(ast_node_t *node)
{
    char **argv = node->data.command->argv;

    for (int i = 1; argv[i] != NULL; i++) {
        if (is_glob_pattern(argv[i])) {
            argv = process_glob_pattern(argv, &i, node);
        }
    }
}

void globbings(ast_node_t *node)
{
    if (!node || node->type != NODE_COMMAND || !node->data.command ||
        !node->data.command->argv)
        return;
    apply_globbing_to_command(node);
}
