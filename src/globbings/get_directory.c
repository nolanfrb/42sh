/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_directory
*/

#include "globbings.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>

static char *join_path(const char *dir, const char *file)
{
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

static void add_to_directory(char ***directory, int *count_files,
    const char *new_path, const char *entry_name)
{
    char *full_path = join_path(new_path, entry_name);

    if (!full_path)
        return;
    *directory = realloc(*directory, sizeof(char *) * (*count_files + 1));
    if (!*directory) {
        free(full_path);
        return;
    }
    (*directory)[*count_files] = strdup(full_path);
    (*count_files)++;
    free(full_path);
}

static void process_directory_entries(DIR *dir, char ***directory,
    int *count_files, const char *new_path)
{
    struct dirent *entry;

    while (1) {
        entry = readdir(dir);
        if (entry == NULL)
            break;
        if (entry->d_name[0] == '.')
            continue;
        add_to_directory(directory, count_files, new_path, entry->d_name);
    }
}

char **get_directory(char *path, int *count)
{
    char *new_path = strtok(path, "*");
    DIR *dir;
    char **directory = NULL;
    int count_files = 0;

    if (new_path == NULL)
        new_path = strdup(".");
    dir = opendir(new_path);
    if (!dir)
        return NULL;
    directory = malloc(sizeof(char *));
    if (!directory) {
        closedir(dir);
        return NULL;
    }
    process_directory_entries(dir, &directory, &count_files, new_path);
    closedir(dir);
    *count = count_files;
    return directory;
}
