/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** alias
*/

#ifndef ALIAS_H_
    #define ALIAS_H_

typedef struct alias_s alias_t;
typedef struct alias_info_s alias_info_t;

struct alias_info_s {
    char *name;
    char *value;
};

struct alias_s {
    alias_info_t **info;
    int nb_alias;
};

alias_t *load_alias(void);
char *get_home_directory(void);
void free_alias(alias_t *alias);
alias_t *init_alias(int count);
int count_aliases(int fd);

#endif /* !ALIAS_H_ */
