/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings
*/

#include "shell.h"
#include "ast.h"
#include "globbings.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fnmatch.h>

char **expand_pattern_recursive(pattern_ctx_t ctx, expansion_result_t
    *result)
{
    result->count = 0;
    if (ctx.comp_idx >= ctx.comp_count)
        return handle_base_case(ctx.base_dir, result);
    if (has_glob_chars(ctx.components[ctx.comp_idx]))
        return process_glob_component(ctx, result);
    else
        return handle_non_glob_component(ctx, result);
}

static const char *get_base_dir_for_pattern(const char *pattern)
{
    return (pattern[0] == '/') ? "/" : ".";
}

char **get_files(const char *pattern, int *count)
{
    char **components;
    int comp_count = 0;
    const char *base_dir;
    expansion_result_t result;
    pattern_ctx_t ctx;

    *count = 0;
    if (!pattern || strlen(pattern) == 0)
        return NULL;
    if (!has_glob_chars(pattern))
        return NULL;
    components = init_pattern_expansion(pattern, &comp_count);
    if (!components)
        return NULL;
    base_dir = get_base_dir_for_pattern(pattern);
    init_expansion_result(&result);
    ctx = create_pattern_ctx(base_dir, components, 0, comp_count);
    result.results = expand_pattern_recursive(ctx, &result);
    *count = result.count;
    return sort_and_clean_results(&result, components);
}

static void free_old_argv(char **argv)
{
    int i;

    for (i = 0; argv[i]; i++)
        free(argv[i]);
    free(argv);
}

void globbings(ast_node_t *node)
{
    int new_argc = 0;
    char **new_argv = NULL;

    if (!node || node->type != NODE_COMMAND)
        return;
    new_argv = expand_arguments(node->data.command->argv, &new_argc);
    if (!new_argv)
        return;
    free_old_argv(node->data.command->argv);
    node->data.command->argv = new_argv;
}
