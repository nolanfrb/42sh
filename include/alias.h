/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** alias
*/

#ifndef ALIAS_H_
    #define ALIAS_H_
    #include "ast.h"
    #define NO_ARGS 1
    #define ONE_ARG 2
    #define TWO_ARGS 3

typedef struct command_node_s command_node_t;
typedef struct alias_s alias_t;
typedef struct alias_info_s alias_info_t;
typedef enum state_e state_t;

enum state_e {
    ALIAS,
    DEFAULT
};

struct alias_info_s {
    char *name;
    char *value;
};

struct alias_s {
    alias_info_t **info;
    int nb_alias;
    state_t state;
};

alias_t *load_alias(void);
char *get_home_directory(void);
void free_alias(alias_t *alias);
alias_t *init_alias(int count);
int count_aliases(int fd);
alias_info_t *extract_alias(char *line, alias_info_t *alias_info);
alias_info_t **parse_alias_file(int fd, alias_t *alias);
int search_alias(alias_t *alias, command_node_t *command, shell_t *shell);
int parse_alias_args(alias_t *alias, char **args);
void print_alias(alias_t *alias, char *name, bool specific);
int add_alias(alias_t *alias, char *alias_name, char *alias_value);
int count_args(char **args);
int builtin_unalias(shell_t *shell, char **args);

#endif /* !ALIAS_H_ */
