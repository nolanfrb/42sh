/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings_handle_case
*/

#include "globbings.h"
#include <stdlib.h>


char **handle_base_case(const char *base_dir, expansion_result_t
    *result)
{
    string_array_t results;

    init_string_results(&results, 2);
    if (!results.array)
        return NULL;
    if (!add_copy_to_array(&results, base_dir)) {
        free_string_array_struct(&results);
        return NULL;
    }
    result->count = results.count;
    return results.array;
}

int handle_terminal_component(char *new_path, string_array_t *results)
{
    if (!add_string_to_array(results, new_path)) {
        free(new_path);
        return 0;
    }
    return 1;
}

int handle_directory_entries(expansion_result_t *sub_result,
    string_array_t *results)
{
    if (!add_entries_to_results(results, sub_result->results,
        sub_result->count)) {
        free_string_array_struct(results);
        return 0;
    }
    return 1;
}

static char **handle_non_directory(char *new_path, expansion_result_t *result)
{
    free(new_path);
    return create_empty_result(result);
}

char **handle_non_glob_component(pattern_ctx_t ctx,
    expansion_result_t *result)
{
    char *new_path;

    new_path = join_path(ctx.base_dir, ctx.components[ctx.comp_idx]);
    if (!new_path)
        return NULL;
    if (ctx.comp_idx == ctx.comp_count - 1)
        return process_last_component(new_path, result);
    if (is_directory(new_path))
        return process_directory_component(new_path, ctx, result);
    return handle_non_directory(new_path, result);
}
