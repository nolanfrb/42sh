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

char **get_directory(char *path, int *count)
{
    char *new_path = strtok(path, "*");
    if (new_path == NULL)
        new_path = strdup(".");
    printf("new_path: %s\n", new_path);
    DIR *dir = opendir(new_path);
    struct dirent *entry;
    char **directory = NULL;
    int count_files = 0;

    if (!dir)
        return NULL;
    directory = malloc(sizeof(char *) * 1);
    if (!directory) {
        closedir(dir);
        return NULL;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        printf("entry: %s\n", entry->d_name);
        if (entry->d_name[0] == '.')
            continue;
        directory = realloc(directory, sizeof(char *) * (count_files + 1));
        if (!directory) {
            closedir(dir);
            return NULL;
        }
        directory[count_files] = strdup(entry->d_name);
        count_files++;
    }
    
    closedir(dir);
    *count = count_files;
    return directory;
}