/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_command
*/

#include "ast.h"
#include <stdio.h>

/**
 * @brief Count the number of arguments in a command
 * @param tokens The token array
 * @param pos Pointer to the current position in the token array
 * @return The number of arguments counted
 */
static int count_command_arguments(char **tokens, int *pos)
{
    int arg_count = 0;
    int start_pos = *pos;

    while (tokens[*pos] && is_special_op(tokens[*pos]) == false) {
        arg_count++;
        (*pos)++;
    }
    *pos = start_pos;
    return arg_count;
}

/**
 * @brief Allocate and populate the argv array for a command
 * @param tokens The token array
 * @param pos Pointer to the current position in the token array
 * @param arg_count The number of arguments to allocate
 * @return The allocated and populated argv array, or NULL on error
 */
static char **create_args_array(char **tokens, int *pos, int arg_count)
{
    char **argv = malloc(sizeof(char *) * (arg_count + 1));
    int start_pos = *pos;

    if (!argv) {
        perror("malloc");
        return NULL;
    }
    for (int i = 0; i < arg_count; i++)
        argv[i] = tokens[start_pos + i];
    argv[arg_count] = NULL;
    *pos += arg_count;
    return argv;
}

/**
 * @brief Create a command node with the given argv
 * @param argv The argv array for the command
 * @return The created command node, or NULL on error
 */
static ast_node_t *create_command_node(char **argv)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));
    command_node_t *command = malloc(sizeof(command_node_t));

    if (!node || !command) {
        perror("malloc");
        free(node);
        free(command);
        free(argv);
        return NULL;
    }
    command->argv = argv;
    node->type = NODE_COMMAND;
    node->data.command = command;
    return node;
}

/**
 * @brief Parse a command from tokens
 * @param tokens The token array
 * @param pos Pointer to the current position in the token array
 * @return The parsed command node, or NULL on error
 */
ast_node_t *parse_command(char **tokens, int *pos)
{
    int arg_count = count_command_arguments(tokens, pos);
    char **arguments = NULL;

    if (arg_count == 0)
        return NULL;
    arguments = create_args_array(tokens, pos, arg_count);
    if (!arguments)
        return NULL;
    return create_command_node(arguments);
}
