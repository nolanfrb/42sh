/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Abstract Syntax Tree (AST) implementation
*/

#include "shell.h"
#include "ast.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ast_node_t *parse_sequence(char **tokens, int *pos)
{
    ast_node_t *left = parse_and_or(tokens, pos);
    ast_node_t *right = NULL;
    ast_node_t *seq = malloc(sizeof(ast_node_t));

    if (!seq) {
        perror("malloc");
        return NULL;
    }
    while (tokens[*pos] && strcmp(tokens[*pos], ";") == 0) {
        (*pos)++;
        right = parse_and_or(tokens, pos);
        seq->type = NODE_SEQUENCE;
        seq->data.binop.left = left;
        seq->data.binop.right = right;
        left = seq;
    }
    return left;
}

ast_node_t *parse_and_or(char **tokens, int *pos)
{
    ast_node_t *left = parse_pipes(tokens, pos);
    node_type_t type;
    ast_node_t *right = NULL;
    ast_node_t *and_or = NULL;

    while (tokens[*pos] && (strcmp(tokens[*pos], "&&") == 0 || strcmp(tokens[*pos], "||") == 0)) {
        and_or = malloc(sizeof(ast_node_t));
        if (!and_or) {
            perror("malloc");
            return NULL;
        }
        type = (strcmp(tokens[*pos], "&&") == 0) ? NODE_AND : NODE_OR;
        (*pos)++;
        right = parse_pipes(tokens, pos);
        and_or->type = type;
        and_or->data.binop.left = left;
        and_or->data.binop.right = right;
        left = and_or;
    }
    return left;
}

ast_node_t *parse_pipes(char **tokens, int *pos)
{
    ast_node_t *left = parse_redirect(tokens, pos);
    ast_node_t *right = NULL;
    ast_node_t *pipe = malloc(sizeof(ast_node_t));

    if (!pipe) {
        perror("malloc");
        return NULL;
    }
    while (tokens[*pos] && strcmp(tokens[*pos], "|") == 0) {
        (*pos)++;
        right = parse_redirect(tokens, pos);
        pipe->type = NODE_PIPE;
        pipe->data.binop.left = left;
        pipe->data.binop.right = right;
        left = pipe;
    }
    return left;
}

ast_node_t *parse_command(char **tokens, int *pos)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));
    command_node_t *command = malloc(sizeof(command_node_t));
    int start_pos = *pos;
    int arg_count = 0;

    if (!node || !command) {
        perror("malloc");
        free(node);
        free(command);
        return NULL;
    }
    while (tokens[*pos] && is_special_op(tokens[*pos]) == false) {
        arg_count++;
        (*pos)++;
    }
    command->argv = malloc(sizeof(char *) * (arg_count + 1));
    if (!command->argv) {
        perror("malloc");
        free(node);
        free(command);
        return NULL;
    }
    for (int i = 0; i < arg_count; i++)
        command->argv[i] = tokens[start_pos + i];
    command->argv[arg_count] = NULL;
    node->type = NODE_COMMAND;
    node->data.command = command;
    return node;
}

ast_node_t *parse_subshell(char **tokens, int *pos)
{
    ast_node_t *node = NULL;
    ast_node_t *child = NULL;

    if (tokens[*pos] && strcmp(tokens[*pos], "(") == 0) {
        (*pos)++;
        child = parse_sequence(tokens, pos);
        if (!child) {
            fprintf(stderr, "error: missing subshell content\n");
            return NULL;
        }
        if (tokens[*pos] && strcmp(tokens[*pos], ")") == 0) {
            (*pos)++;
            node = malloc(sizeof(ast_node_t));
            if (!node) {
                perror("malloc");
                return NULL;
            }
            node->type = NODE_SUBSHELL;
            node->data.subshell.child = child;
        } else {
            fprintf(stderr, "error: missing closing parenthesis\n");
            free(child);
            return NULL;
        }
    } else {
        node = parse_command(tokens, pos);
    }
    return node;
}


