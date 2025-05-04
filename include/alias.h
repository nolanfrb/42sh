/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** alias
*/

#ifndef ALIAS_H_
    #define ALIAS_H_
    #include "ast.h"

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

#endif /* !ALIAS_H_ */