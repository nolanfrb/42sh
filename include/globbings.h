/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings
*/

#ifndef INCLUDED_GLOBBINGS_H
    #define INCLUDED_GLOBBINGS_H
    #include "ast.h"

struct recursive_data {
    int *count;
    int deepth;
    int max_deepth;
} typedef recursive_data_t;

/*utility function to get a list of all the file*/
char **get_files(const char *path, int *count);
//void get_all_files_recursive(char *base_path, char ***files, recursive_data_t *data);

int globbings(ast_node_t *node);

#endif
