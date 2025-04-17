/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtins
*/

#include "shell.h"
#include "ast.h"
#include <sys/types.h>

static const builtin_t builtins[] = {
    {"cd", &builtin_cd},
    {"exit", &builtin_exit},
    {"setenv", &builtin_setenv},
    {"unsetenv", &builtin_unsetenv},
    {"env", &builtin_env},
    {"echo", &builtin_echo},
    {NULL, NULL}
};

const builtin_t *get_builtins(void)
{
    return builtins;
}
