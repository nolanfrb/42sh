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

int is_directory(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

char *join_path(const char *dir, const char *file) {
    size_t len = strlen(dir) + strlen(file) + 2;
    char *full = malloc(len);
    if (!full)
        return NULL;
    snprintf(full, len, "%s/%s", dir, file);
    return full;
}

void get_all_files_recursive(const char *base_path, char ***files, int *count) {
    DIR *dir = opendir(base_path);
    struct dirent *entry;
    char *full_path = NULL;

    if (!dir)
        return;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        full_path = join_path(base_path, entry->d_name);
        if (!full_path)
            continue;
        if (is_directory(full_path)) {
            get_all_files_recursive(full_path, files, count);
        } else {
            *files = realloc(*files, sizeof(char *) * (*count + 1));
            if (!*files)
                return;
            (*files)[*count] = full_path;
            (*count)++;
            continue;
        }
        free(full_path);
    }
    closedir(dir);
}

char **get_files(const char *start_path, int *count) {
    char **files = NULL;

    *count = 0;
    get_all_files_recursive(start_path, &files, count);
    printf("%i\n", (*count));
    for (int i = 0; files[i]; i++) {
        printf("%s\n", files[i]);
    }
    return files;
}
