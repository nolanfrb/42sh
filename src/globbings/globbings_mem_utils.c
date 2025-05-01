/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings_array
*/

#include "globbings.h"
#include <stdlib.h>

void init_string_array(string_array_t *arr, int initial_capacity)
{
    arr->array = malloc(sizeof(char *) * initial_capacity);
    if (!arr->array) {
        arr->capacity = 0;
        arr->count = 0;
        return;
    }
    arr->capacity = initial_capacity;
    arr->count = 0;
    if (arr->array)
        arr->array[0] = NULL;
}

void free_string_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

void free_string_array_struct(string_array_t *array)
{
    if (!array)
        return;
    free_string_array(array->array);
    array->array = NULL;
    array->count = 0;
    array->capacity = 0;
}

void init_string_results(string_array_t *results, int capacity)
{
    init_string_array(results, capacity);
}

char **init_pattern_expansion(const char *pattern, int *comp_count)
{
    return split_path(pattern, comp_count);
}
