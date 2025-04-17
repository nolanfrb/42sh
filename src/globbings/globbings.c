/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings
*/

#include "ast.h"
#include "globbings.h"
#include <stdio.h>
#include <fnmatch.h>

static int check_globbings(ast_node_t *node)
{
    if (node->type != NODE_COMMAND)
        return -1;
    for (int i = 1; node->data.command->argv[i]; i++) {
        if (fnmatch("*.c", node->data.command->argv[i], 0) == 0)
            printf("in the if \n");
    }
}

int globbings(ast_node_t *node)
{
    int count = 0;
    char **files;

    files = get_files(node->data.command->argv[1], &count);
}
