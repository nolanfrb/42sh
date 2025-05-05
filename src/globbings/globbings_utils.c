/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings_utils
*/

#include <stdio.h>
#include "globbings.h"
#include <string.h>

int count_old_args(char **argv)
{
    int count = 0;

    while (argv[count] != NULL)
        count++;
    return count;
}

void free_old_args(char **argv)
{
    if (!argv)
        return;
    for (int i = 0; argv[i] != NULL; i++)
        free(argv[i]);
    free(argv);
}

void copy_args(update_args_data_t *data, char **src, int start, int end)
{
    for (int i = start; i < end; i++) {
        data->new_argv[data->new_idx] = strdup(src[i]);
        data->new_idx++;
    }
}

int is_glob_pattern(const char *str)
{
    if (!str)
        return 0;
    return (strchr(str, '*') != NULL || strchr(str, '?') != NULL ||
    strchr(str, '[') != NULL || strchr(str, '~') != NULL);
}

void free_selected_files(char **selected_files)
{
    if (!selected_files)
        return;
    for (int i = 0; selected_files[i] != NULL; i++)
        free(selected_files[i]);
    free(selected_files);
}
