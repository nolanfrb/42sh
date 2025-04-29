/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_globbings_main_function
*/

#include <criterion/criterion.h>
#include <criterion/hooks.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "globbings.h"

Test(globbings, null_node)
{
    ast_node_t *node = NULL;

    globbings(node);
    cr_assert_null(node);
}

Test(globbings, not_a_command)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));
    node->type = NODE_AND;

    globbings(node);
    cr_assert_eq(node->type, NODE_AND);
    free(node);
}

Test(globbings, simple_list)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));
    node->type = NODE_COMMAND;
    node->data.command = malloc(sizeof(command_t));
    node->data.command->argv = malloc(sizeof(char *) * 3);
    node->data.command->argv[0] = strdup("ls");
    node->data.command->argv[1] = strdup("src/*.c");
    node->data.command->argv[2] = NULL;

    globbings(node);
    cr_assert_eq(node->type, NODE_COMMAND);
    cr_assert_str_eq(node->data.command->argv[0], "ls");
    cr_assert_str_eq(node->data.command->argv[1], "src/main.c");
    cr_assert_null(node->data.command->argv[2]);

    free(node->data.command->argv[0]);
    free(node->data.command->argv[1]);
    free(node->data.command);
    free(node);
}

Test(globbings, simple_directory)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));
    node->type = NODE_COMMAND;
    node->data.command = malloc(sizeof(command_t));
    node->data.command->argv = malloc(sizeof(char *) * 3);
    node->data.command->argv[0] = strdup("ls");
    node->data.command->argv[1] = strdup("tests/globbings/*");
    node->data.command->argv[2] = NULL;

    globbings(node);
    cr_assert_eq(node->type, NODE_COMMAND);
    int i;
    for (i = 0; node->data.command->argv[i] != NULL; i++);
    cr_assert_eq(i, 5);
    for (int j = 0; j < i; j++) {
        cr_assert_not_null(node->data.command->argv[j]);
    }
    for (int j = 0; j < i; j++) {
        free(node->data.command->argv[j]);
    }
    free(node->data.command);
    free(node);
}