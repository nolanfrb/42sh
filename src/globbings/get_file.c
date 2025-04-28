/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_file
*/

#include "ast.h"
#include <dirent.h>
#include <fnmatch.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "globbings.h"

static int is_directory(const char *path)
{
    struct stat st;

    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

static char *join_path(const char *dir, const char *file)
{
    size_t len = strlen(dir) + strlen(file) + 2;
    char *full = malloc(len);
    char *wildcard;

    if (!full)
        return NULL;
    if (dir[strlen(dir) - 1] == '/')
        snprintf(full, len, "%s%s", dir, file);
    else {
        wildcard = strchr(dir, '*');
        if (wildcard) {
            snprintf(full, len, "%.*s%s", (int)(wildcard - dir), dir, file);
        } else {
            snprintf(full, len, "%s/%s", dir, file);
        }
    }
    return full;
}

static int get_max_deepth(const char *path)
{
    int depth = 1;
    const char *p = path;

    while (*p) {
        if (*p == '/')
            depth++;
        p++;
    }
    return depth;
}

static void process_directory_entry(const char *base_path, struct dirent *entry, recursive_data_t *data, int deepth)
{
    char *full_path = join_path(base_path, entry->d_name);

    if (!full_path)
        return;
    if (is_directory(full_path)) {
        printf("directory : %s\n", full_path);
        get_all_files_recursive(full_path, deepth, data);
    } else {
        data->files = realloc(data->files, sizeof(char *) * (*data->count + 1));
        if (!data->files) {
            free(full_path);
            return;
        }
        (data->files)[*data->count] = full_path;
        printf("file_in_array : %s\n", full_path);
        (*data->count)++;
    }
}

void get_all_files_recursive(const char *base_path, int deepth, recursive_data_t *data)
{
    char *base_path_copy = strdup(base_path);
    char *new_path;
    DIR *dir;
    struct dirent *entry;

    printf("base_path: %s\n", base_path);
    if (!base_path_copy)
        return;  
    new_path = strtok(base_path_copy, "*");
    if (new_path == NULL)
        new_path = ".";
    dir = opendir(new_path);
    deepth += 1;
    if (!dir || deepth >= data->max_deepth) {
        if (dir)
            closedir(dir);
        free(base_path_copy);
        printf("returning\n");
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.' || strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;
        process_directory_entry(base_path, entry, data, deepth);
    }
    closedir(dir);
    free(base_path_copy);
}

char **get_files(const char *start_path, int *count)
{
    recursive_data_t *data = malloc(sizeof(recursive_data_t));
    char *begining_directory;

    if (!data)
        return NULL;
    if (start_path == NULL || start_path[0] == '\0')
        return NULL;
    data->count = count;
    data->deepth = 0;
    data->max_deepth = get_max_deepth(start_path);
    printf("file max deepth: %i\n", data->max_deepth);
    printf("start_path: %s\n", start_path);
    get_all_files_recursive(start_path, 0, data);
    free(data);
    return data->files;
}
