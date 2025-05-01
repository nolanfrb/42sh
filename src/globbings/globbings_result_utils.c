/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings_result_utils
*/

#include "globbings.h"
#include <stdlib.h>

char **create_empty_result(expansion_result_t *result)
{
    string_array_t results;

    init_string_results(&results, 1);
    result->count = 0;
    return results.array;
}

void init_expansion_result(expansion_result_t *result)
{
    result->results = NULL;
    result->count = 0;
}

int add_entries_to_results(string_array_t *results, char **entries,
    int count)
{
    int i;

    for (i = 0; i < count; i++) {
        if (!add_string_to_array(results, entries[i]))
            return 0;
    }
    free(entries);
    return 1;
}

char **sort_and_clean_results(expansion_result_t *result,
    char **components)
{
    if (result->results && result->count > 1)
        qsort(result->results, result->count, sizeof(char *), compare_strings);
    free_string_array(components);
    return result->results;
}
