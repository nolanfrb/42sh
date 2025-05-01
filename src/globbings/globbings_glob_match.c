/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings_pattern_match
*/

#include "globbings.h"
#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>

int has_glob_chars(const char *str)
{
    return (strchr(str, '*') != NULL || strchr(str, '?') != NULL ||
            strchr(str, '[') != NULL);
}

int match_directory_entries(char **dir_entries, int dir_count,
    pattern_ctx_t ctx, string_array_t *results)
{
    int i;

    for (i = 0; i < dir_count; i++) {
        if (fnmatch(ctx.components[ctx.comp_idx], dir_entries[i], 0) == 0) {
            if (!process_directory_entry(ctx, dir_entries[i], results))
                return 0;
        }
    }
    return 1;
}

match_result_t create_match_result(char **matches, int count)
{
    match_result_t result;

    result.matches = matches;
    result.count = count;
    return result;
}

match_result_t handle_no_matches(const char *arg)
{
    string_array_t matches;
    match_result_t result;

    init_string_array(&matches, 2);
    if (!matches.array) {
        result.matches = NULL;
        result.count = 0;
        return result;
    }
    if (!add_copy_to_array(&matches, arg)) {
        free_string_array_struct(&matches);
        result.matches = NULL;
        result.count = 0;
        return result;
    }
    result.matches = matches.array;
    result.count = matches.count;
    return result;
}

static int add_expanded_matches(string_array_t *result, match_result_t matches)
{
    int j;

    for (j = 0; j < matches.count; j++) {
        if (!add_copy_to_array(result, matches.matches[j]))
            return 0;
    }
    return 1;
}

int handle_glob_matches(match_result_t matches, arg_context_t *ctx)
{
    if (!resize_result_array(ctx->result, matches.count,
        ctx->remaining_args)) {
        free_string_array(matches.matches);
        return 0;
    }
    if (!add_expanded_matches(ctx->result, matches)) {
        free_string_array(matches.matches);
        return 0;
    }
    free_string_array(matches.matches);
    return 1;
}
