/*
** EPITECH PROJECT, 2025
** minishell_project
** File description:
** test_env_init
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "env.h"

Test(init_shell, should_initialize_shell_with_env)
{
    char *env[] = {"USER=loann", "PATH=/usr/bin", NULL};
    shell_t *shell = init_shell(env);

    cr_assert_not_null(shell);
    cr_assert_eq(shell->env_size, 2);
    cr_assert_str_eq(shell->env_array[0], "USER=loann");
    cr_assert_str_eq(shell->env_array[1], "PATH=/usr/bin");
    cr_assert_null(shell->env_array[2]);
    cr_assert_eq(shell->exit_code, 0);

    free(shell->env_array[0]);
    free(shell->env_array[1]);
    free(shell->env_array);
    free(shell);
}

Test(init_shell, should_handle_empty_env)
{
    char *env[] = {NULL};
    shell_t *shell = init_shell(env);

    cr_assert_not_null(shell);
    cr_assert_eq(shell->env_size, 0);
    cr_assert_not_null(shell->env_array);
    cr_assert_null(shell->env_array[0]);

    free(shell->env_array);
    free(shell);
}
