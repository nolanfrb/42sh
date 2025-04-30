/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** test_env_free
*/

#include <criterion/criterion.h>
#include <criterion/hooks.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "env.h"
#include "src/commands/builtins/env/env_free.c"

Test(free_shell, should_not_crash_if_shell_is_null)
{
    free_shell(NULL);
    cr_assert(1); // Ne doit pas segfault
}

Test(free_shell, should_not_crash_if_env_array_is_null)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->env_array = NULL;
    shell->local_vars = NULL;
    shell->env_size = 0;

    free_shell(shell);
    cr_assert(1); // Ne doit pas segfault
}

Test(free_shell, should_free_env_array_properly)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->env_size = 2;
    shell->env_array = malloc(sizeof(char *) * 2);
    shell->env_array[0] = strdup("VAR1=value");
    shell->env_array[1] = strdup("VAR2=value");
    shell->local_vars = NULL;

    free_shell(shell);
    cr_assert(1); // Libération correcte sans crash
}

Test(free_shell, should_free_local_vars_properly)
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->env_size = 2;
    shell->local_vars = malloc(sizeof(char *) * 2);
    shell->local_vars[0] = strdup("VAR1=local");
    shell->local_vars[1] = strdup("VAR2=local");
    shell->env_array = NULL;

    free_shell(shell);
    cr_assert(1);
}