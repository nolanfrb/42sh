/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtins
*/

#include "builtins.h"
#include "ast.h"
#include <sys/types.h>

static const builtin_t builtins[] = {
    {"cd", &builtin_cd},
    {"exit", &builtin_exit},
    {"setenv", &builtin_setenv},
    {"unsetenv", &builtin_unsetenv},
    {"env", &builtin_env},
    {"echo", &builtin_echo},
    {"history", &builtin_history},
    {"alias", &builtin_alias},
    {"unalias", &builtin_unalias},
    {NULL, NULL}
};

const builtin_t *get_builtins(void)
{
    return builtins;
}
