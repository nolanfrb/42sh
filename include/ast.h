/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** ast
*/

#ifndef INCLUDED_AST_H
    #define INCLUDED_AST_H

typedef struct word_info {
    int start;
    char **words;
    int word_idx;
} word_info_t;

char **lexer(char *cmd_line);
#endif
