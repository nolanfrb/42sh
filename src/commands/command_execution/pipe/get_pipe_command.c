/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_pipe_command
*/

#include "command.h"
#include "shell.h"
#include "ast.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

static int count_pipe_commands_recursive(ast_node_t *node)
{
    if (!node)
        return 0;
    if (node->type == NODE_PIPE) {
        if (node->data.binop.left == NULL ||
            node->data.binop.right == NULL) {
            return 0;
        }
        return count_pipe_commands_recursive(node->data.binop.left) +
        count_pipe_commands_recursive(node->data.binop.right);
    } else {
        return 1;
    }
}

static void collect_pipe_commands_recursive(ast_node_t *node,
    ast_node_t **commands, int *index)
{
    if (!node)
        return;
    if (node->type == NODE_PIPE) {
        if (node->data.binop.left) {
            collect_pipe_commands_recursive(node->data.binop.left, commands,
                index);
        }
        if (node->data.binop.right) {
            collect_pipe_commands_recursive(node->data.binop.right, commands,
                index);
        }
    } else {
        commands[*index] = node;
        (*index)++;
    }
}

static void fill_pipe_commands(ast_node_t *node, ast_node_t **commands)
{
    int index = 0;

    collect_pipe_commands_recursive(node, commands, &index);
}

ast_node_t **collect_pipe_commands(ast_node_t *node, int *count)
{
    ast_node_t **commands;

    *count = count_pipe_commands_recursive(node);
    commands = malloc(sizeof(ast_node_t *) * (*count));
    if (!commands)
        return NULL;
    fill_pipe_commands(node, commands);
    return commands;
}
