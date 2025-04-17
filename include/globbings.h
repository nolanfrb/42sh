/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings
*/

#ifndef INCLUDED_GLOBBINGS_H
    #define INCLUDED_GLOBBINGS_H
    #include "ast.h"

char **get_files(const char *path, int *count);
int globbings(ast_node_t *node);

#endif
