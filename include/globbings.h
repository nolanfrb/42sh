/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings
*/

#ifndef INCLUDED_GLOBBINGS_H
    #define INCLUDED_GLOBBINGS_H
    #include "ast.h"

typedef struct {
    int new_idx;
    char **new_argv;
} update_args_data_t;

void globbings(ast_node_t *node);
// Utils functions
void free_selected_files(char **selected_files);
int is_glob_pattern(const char *str);
int count_old_args(char **argv);
void copy_args(update_args_data_t *data, char **src, int start, int end);
void free_old_args(char **argv);
#endif
