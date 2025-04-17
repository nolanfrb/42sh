/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_cd
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "env.h"
#include <sys/stat.h>

static char *expand_tilde(shell_t *shell, char *arg)
{
    char *home = get_env_value(shell, "HOME");
    char *path = NULL;
    size_t len_home;
    size_t len_arg;

    if (!home)
        return NULL;
    len_home = strlen(home);
    len_arg = strlen(arg);
    path = malloc(len_home + len_arg);
    if (!path)
        return NULL;
    strcpy(path, home);
    strcat(path, arg + 1);
    return path;
}

static void update_oldpwd(shell_t *shell, char *old_pwd)
{
    if (!old_pwd)
        return;
    set_env_value(shell, "OLDPWD", old_pwd);
}

static char *get_target_directory(shell_t *shell, char *arg)
{
    char *oldpwd_value;

    if (!arg || strcmp(arg, "") == 0)
        return get_env_value(shell, "HOME");
    if (arg[0] == '~')
        return expand_tilde(shell, arg);
    if (strcmp(arg, "..") == 0)
        return "..";
    if (strcmp(arg, "-") == 0) {
        oldpwd_value = get_env_value(shell, "OLDPWD");
        if (!oldpwd_value) {
            printf(": No such file or directory.\n");
            shell->exit_code = 1;
            return NULL;
        }
        return oldpwd_value;
    }
    return arg;
}

static int check_cd_conditions(shell_t *shell, char *target_dir, char *old_pwd)
{
    struct stat path_stat;

    if (!target_dir) {
        printf("cd: HOME not set\n");
        shell->exit_code = 1;
        free(old_pwd);
        return 1;
    }
    if (stat(target_dir, &path_stat) == 0 && !S_ISDIR(path_stat.st_mode)) {
        printf("%s", target_dir);
        printf(": Not a directory.\n");
        shell->exit_code = 1;
        free(old_pwd);
        return 1;
    }
    return 0;
}

static int handle_cd_errors(shell_t *shell, char *target_dir, char *old_pwd)
{
    if (check_cd_conditions(shell, target_dir, old_pwd))
        return 1;
    if (chdir(target_dir) == -1) {
        printf("%s", target_dir);
        printf(": No such file or directory.\n");
        shell->exit_code = 1;
        free(old_pwd);
        return 1;
    }
    return 0;
}

static int handle_cd_target_error(
    shell_t *shell, char *target_dir, char *old_pwd, int needs_free)
{
    if (!target_dir) {
        printf("cd: HOME not set\n");
        shell->exit_code = 1;
        free(old_pwd);
        return 1;
    }
    if (handle_cd_errors(shell, target_dir, old_pwd)) {
        if (needs_free)
            free(target_dir);
        return 1;
    }
    return 0;
}

int builtin_cd(shell_t *shell, char **args)
{
    char *old_pwd = getcwd(NULL, 0);
    char *target_dir = get_target_directory(shell, args[1]);
    int needs_free = 0;

    if (args[1] && args[1][0] == '~')
        needs_free = 1;
    if (args[1] && strcmp(args[1], "-") == 0)
        return 1;
    if (handle_cd_target_error(shell, target_dir, old_pwd, needs_free))
        return 1;
    update_oldpwd(shell, old_pwd);
    if (needs_free)
        free(target_dir);
    free(old_pwd);
    return 0;
}
