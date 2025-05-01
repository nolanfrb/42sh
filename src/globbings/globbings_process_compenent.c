/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings_process_compenent
*/

#include "globbings.h"
#include <stdlib.h>

pattern_ctx_t create_pattern_ctx(const char *base_dir, char **components
    , int comp_idx, int comp_count)
{
    pattern_ctx_t ctx;

    ctx.base_dir = base_dir;
    ctx.components = components;
    ctx.comp_idx = comp_idx;
    ctx.comp_count = comp_count;
    return ctx;
}

static int process_subdir_component(pattern_ctx_t ctx, char *new_path,
    string_array_t *results)
{
    expansion_result_t sub_result;
    pattern_ctx_t sub_ctx;

    init_expansion_result(&sub_result);
    sub_ctx = create_pattern_ctx(new_path, ctx.components,
        ctx.comp_idx + 1, ctx.comp_count);
    sub_result.results = expand_pattern_recursive(sub_ctx, &sub_result);
    if (!sub_result.results) {
        free(new_path);
        return 1;
    }
    return handle_directory_entries(&sub_result, results);
}

char **process_directory_component(char *new_path, pattern_ctx_t ctx,
    expansion_result_t *result)
{
    char **results = NULL;
    expansion_result_t sub_result;
    pattern_ctx_t sub_ctx;

    init_expansion_result(&sub_result);
    sub_ctx = create_pattern_ctx(new_path, ctx.components, ctx.comp_idx + 1
        , ctx.comp_count);
    results = expand_pattern_recursive(sub_ctx, &sub_result);
    result->count = sub_result.count;
    free(new_path);
    return results;
}

int process_directory_entry(pattern_ctx_t ctx, char *entry_name,
    string_array_t *results)
{
    char *new_path;

    new_path = join_path(ctx.base_dir, entry_name);
    if (!new_path)
        return 1;
    if (ctx.comp_idx == ctx.comp_count - 1)
        return handle_terminal_component(new_path, results);
    if (is_directory(new_path))
        return process_subdir_component(ctx, new_path, results);
    free(new_path);
    return 1;
}

char **process_glob_component(pattern_ctx_t ctx,
    expansion_result_t *result)
{
    char **dir_entries;
    int dir_count = 0;
    string_array_t results;

    init_string_results(&results, 10);
    if (!results.array)
        return NULL;
    dir_entries = get_directory(ctx.base_dir, &dir_count);
    if (!dir_entries) {
        free_string_array_struct(&results);
        return NULL;
    }
    if (!match_directory_entries(dir_entries, dir_count, ctx, &results)) {
        free_string_array(dir_entries);
        return NULL;
    }
    free_string_array(dir_entries);
    result->count = results.count;
    return results.array;
}

char **process_last_component(char *new_path, expansion_result_t
    *result)
{
    string_array_t results;

    init_string_array(&results, 2);
    if (!results.array) {
        free(new_path);
        return NULL;
    }
    if (!add_string_to_array(&results, new_path)) {
        free(new_path);
        free(results.array);
        return NULL;
    }
    result->count = results.count;
    return results.array;
}
