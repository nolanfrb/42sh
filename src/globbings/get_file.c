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

static int is_directory(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

static char *join_path(const char *dir, const char *file) {
    size_t len = strlen(dir) + strlen(file) + 2;
    char *full = malloc(len);
    if (!full)
        return NULL;
    if (dir[strlen(dir) - 1] == '/')
        snprintf(full, len, "%s%s", dir, file);
    else
        snprintf(full, len, "%s/%s", dir, file);
    return full;
}

static int max_deepth(const char *path) {
    int depth = 1;
    const char *p = path;

    while (*p) {
        if (*p == '/')
            depth++;
        p++;
    }
    return depth;
}

static void get_all_files_recursive(const char *base_path, char ***files, int *count, int deepth, int max_deepth, recursive_data_t *data) {
    char *new_path = strtok(base_path, "*");
    if (new_path == NULL)
        new_path = strdup(".");
    DIR *dir = opendir(new_path);
    struct dirent *entry;
    char *full_path = NULL;

    
    deepth += 1;
    if (!dir)
        return;
    if (deepth >= data->max_deepth) {
        closedir(dir);
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        printf("file entry: %s\n", entry->d_name);
        if (entry->d_name[0] == '.')
            continue;
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        full_path = join_path(base_path, entry->d_name);
        if (!full_path)
            continue;
        if (is_directory(full_path)) {
            get_all_files_recursive(full_path, files, count, deepth, max_deepth, data);
        } else {
            *files = realloc(*files, sizeof(char *) * (*data->count + 1));
            if (!*files)
                return;
            (*files)[*data->count] = full_path;
            (*data->count)++;
            continue;
        }
        free(full_path);
    }
    closedir(dir);
}

char **get_files(const char *start_path, int *count) {
    char **files = NULL;
    recursive_data_t *data = malloc(sizeof(recursive_data_t));
    if (!data)
        return NULL;
    if (start_path == NULL || start_path[0] == '\0')
        return NULL;
    data->count = count;
    data->deepth = 0;
    data->max_deepth = max_deepth(start_path);
    printf("file max deepth: %i\n", data->max_deepth);
    get_all_files_recursive(start_path, &files, count, 0, max_deepth(start_path), data);
    return files;
}
