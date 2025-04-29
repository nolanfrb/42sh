/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings
*/

#ifndef INCLUDED_GLOBBINGS_H
    #define INCLUDED_GLOBBINGS_H
    #include "ast.h"

typedef struct recursive_data {
    int *count;
    int deepth;
    int max_deepth;
    char **files;
} recursive_data_t;

char **get_files(const char *path, int *count);
char **get_directory(char *path, int *count);
void get_all_files_recursive(const char *base_path, int deepth,
    recursive_data_t *data);

void globbings(ast_node_t *node);

void free_selected_files(char **selected_file);
void free_files(char **files, int count);
void free_var(char **selected_file, char **files, char *pattern, int count);

#endif
