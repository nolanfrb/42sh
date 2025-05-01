/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings_path_split
*/

#include "globbings.h"

int count_arguments(char **argv)
{
    int count = 0;

    while (argv[count])
        count++;
    return count;
}

static match_result_t expand_argument(const char *arg)
{
    char **matches;
    int count = 0;

    matches = get_files(arg, &count);
    if (!matches || count == 0)
        return handle_no_matches(arg);
    return create_match_result(matches, count);
}

static int process_glob_argument(arg_context_t *ctx)
{
    match_result_t matches;

    matches = expand_argument(ctx->argv[ctx->index]);
    if (!matches.matches)
        return 0;
    return handle_glob_matches(matches, ctx);
}

static int process_regular_argument(arg_context_t *ctx)
{
    return add_copy_to_array(ctx->result, ctx->argv[ctx->index]);
}

int process_single_argument(arg_context_t *ctx)
{
    if (has_glob_chars(ctx->argv[ctx->index])) {
        return process_glob_argument(ctx);
    }
    return process_regular_argument(ctx);
}

char **expand_arguments(char **argv, int *argc)
{
    int arg_count;
    string_array_t result;
    arg_context_t ctx;

    arg_count = count_arguments(argv);
    init_string_array(&result, arg_count + 1);
    if (!result.array)
        return NULL;
    for (int i = 0; i < arg_count; i++) {
        ctx.argv = argv;
        ctx.index = i;
        ctx.result = &result;
        ctx.remaining_args = arg_count - i - 1;
        if (!process_single_argument(&ctx)) {
            free_string_array_struct(&result);
            return NULL;
        }
    }
    *argc = result.count;
    return result.array;
}
