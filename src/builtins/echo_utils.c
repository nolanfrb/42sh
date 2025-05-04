/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** echo_utils
*/

#include "shell.h"
#include "env.h"
#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int is_double_quoted(char *str)
{
    int len = strlen(str);
    int has_min_len = len >= 2;
    int has_start_quote = str[0] == '"';
    int has_end_quote = str[len - 1] == '"';

    if (!has_min_len)
        return 0;
    if (!has_start_quote)
        return 0;
    if (!has_end_quote)
        return 0;
    return 1;
}

int is_single_quoted(char *str)
{
    int len = strlen(str);
    int has_min_len = len >= 2;
    int has_start_quote = str[0] == '\'';
    int has_end_quote = str[len - 1] == '\'';

    if (!has_min_len)
        return 0;
    if (!has_start_quote)
        return 0;
    if (!has_end_quote)
        return 0;
    return 1;
}

static char *remove_quotes(char *str)
{
    int len = strlen(str);
    char *new_str = malloc(len - 1);

    if (!new_str)
        return NULL;
    strncpy(new_str, str + 1, len - 2);
    new_str[len - 2] = '\0';
    return new_str;
}

void print_env_variable(shell_t *shell, char *var)
{
    char *value = NULL;
    
    if (strcmp(var, "$?") == 0) {
        printf_flush("%d", shell->exit_code);
        return;
    }
    value = get_env_value(shell, var + 1);
    if (!value) {
        printf_flush("%s: Undefined variable.\n", var + 1);
        shell->exit_code = 1;
        return;
    }
    printf_flush("%s", value);
    shell->exit_code = 0;
}

static void print_quoted_env(shell_t *shell, char *unquoted)
{
    print_env_variable(shell, unquoted);
}

static void print_quoted_string(char *arg, char *unquoted)
{
    if (unquoted)
        printf_flush("%s", unquoted);
    else
        printf_flush("%s", arg);
}

void handle_double_quotes(shell_t *shell, char *arg)
{
    char *unquoted = remove_quotes(arg);

    if (!unquoted) {
        printf_flush("%s", arg);
        return;
    }
    if (unquoted[0] == '$')
        print_quoted_env(shell, unquoted);
    else
        print_quoted_string(arg, unquoted);
    free(unquoted);
}

void print_single_quoted(char *arg)
{
    char *unquoted = remove_quotes(arg);

    if (!unquoted) {
        printf_flush("%s", arg);
        return;
    }
    printf_flush("%s", unquoted);
    free(unquoted);
}
