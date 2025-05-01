/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings_dir_scan
*/

#include "globbings.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int is_directory(const char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) != 0)
        return 0;
    return S_ISDIR(path_stat.st_mode);
}

static char *prepare_dir_path(const char *dir_path)
{
    char *path;
    size_t len;

    path = strdup(dir_path);
    if (!path)
        return NULL;
    len = strlen(path);
    if (len > 0 && path[len - 1] == '/')
        path[len - 1] = '\0';
    return path;
}

static int read_dir_entry(DIR *dir, string_array_t *files)
{
    struct dirent *entry;

    entry = readdir(dir);
    if (!entry)
        return 0;
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        return 1;
    if (!add_copy_to_array(files, entry->d_name))
        return -1;
    return 1;
}

static int read_all_dir_entries(DIR *dir, string_array_t *files)
{
    int result;

    result = read_dir_entry(dir, files);
    while (result > 0) {
        result = read_dir_entry(dir, files);
    }
    return (result == 0) ? 1 : 0;
}

static char **create_dir_file_list(DIR *dir, int *count)
{
    string_array_t files;
    char **result;

    init_string_array(&files, 10);
    if (!files.array)
        return NULL;
    if (!read_all_dir_entries(dir, &files)) {
        free_string_array_struct(&files);
        return NULL;
    }
    *count = files.count;
    result = files.array;
    return result;
}

int compare_strings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

static char **sort_dir_entries(char **files, int count)
{
    if (files && count > 0)
        qsort(files, count, sizeof(char *), compare_strings);
    return files;
}

char **get_directory(const char *dir_path, int *count)
{
    DIR *dir;
    char **files = NULL;
    char *path;

    *count = 0;
    path = prepare_dir_path(dir_path);
    if (!path)
        return NULL;
    dir = opendir(path);
    if (!dir) {
        free(path);
        return NULL;
    }
    files = create_dir_file_list(dir, count);
    closedir(dir);
    free(path);
    return sort_dir_entries(files, *count);
}
