/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings_arg_expand
*/

#include "globbings.h"
#include <stdlib.h>
#include <string.h>

int process_token(string_array_t *components, char *token)
{
    return add_copy_to_array(components, token);
}

static int expand_array_if_needed(string_array_t *arr)
{
    int new_capacity;
    char **temp;

    if (arr->count >= arr->capacity - 1) {
        new_capacity = arr->capacity * 2;
        temp = realloc(arr->array, sizeof(char *) * new_capacity);
        if (!temp)
            return 0;
        arr->array = temp;
        arr->capacity = new_capacity;
    }
    return 1;
}

int add_string_to_array(string_array_t *arr, char *str)
{
    if (!expand_array_if_needed(arr))
        return 0;
    arr->array[arr->count] = str;
    arr->count++;
    arr->array[arr->count] = NULL;
    return 1;
}

int add_copy_to_array(string_array_t *arr, const char *str)
{
    char *copy;

    copy = strdup(str);
    if (!copy)
        return 0;
    if (!add_string_to_array(arr, copy)) {
        free(copy);
        return 0;
    }
    return 1;
}

char **resize_result_array(string_array_t *result, int match_count,
    int remaining_args)
{
    int new_capacity;
    char **temp;

    new_capacity = result->capacity;
    while (result->count + match_count + remaining_args + 1 > new_capacity)
        new_capacity *= 2;
    if (new_capacity != result->capacity) {
        temp = realloc(result->array, sizeof(char *) * new_capacity);
        if (!temp)
            return NULL;
        result->array = temp;
        result->capacity = new_capacity;
    }
    return result->array;
}
