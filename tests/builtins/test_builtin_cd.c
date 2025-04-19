/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** test_builtin_cd
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"
#include "builtins.h"
#include "src/builtins/builtin_cd.c"

void redirect_all_stdout_cd(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(get_target_directory, should_return_home_if_no_arg)
{
    shell_t shell = {0};
    shell.env_array = malloc(sizeof(char *) * 2);
    shell.env_array[0] = strdup("HOME=/home/user");
    shell.env_array[1] = NULL;
    shell.env_size = 1;

    char *result = get_target_directory(&shell, NULL);

    cr_assert_str_eq(result, "/home/user");

    free(shell.env_array[0]);
    free(shell.env_array);
}

Test(get_target_directory, should_expand_tilde)
{
    shell_t shell = {0};
    shell.env_array = malloc(sizeof(char *) * 2);
    shell.env_array[0] = strdup("HOME=/home/user");
    shell.env_array[1] = NULL;
    shell.env_size = 1;

    char *result = get_target_directory(&shell, "~/Documents");

    cr_assert_str_eq(result, "/home/user/Documents");
    free(result);
    free(shell.env_array[0]);
    free(shell.env_array);
}

Test(get_target_directory, should_return_dotdot_for_double_dot)
{
    shell_t shell = {0};

    char *result = get_target_directory(&shell, "..");

    cr_assert_str_eq(result, "..");
}

Test(get_target_directory, should_handle_dash_with_oldpwd_set)
{
    shell_t shell = {0};
    shell.env_array = malloc(sizeof(char *) * 2);
    shell.env_array[0] = strdup("OLDPWD=/old/path");
    shell.env_array[1] = NULL;
    shell.env_size = 1;

    char *result = get_target_directory(&shell, "-");

    cr_assert_str_eq(result, "/old/path");

    free(shell.env_array[0]);
    free(shell.env_array);
}

Test(get_target_directory, should_handle_dash_with_no_oldpwd, .init = redirect_all_stdout_cd)
{
    shell_t shell = {0};

    char *result = get_target_directory(&shell, "-");

    cr_assert_null(result);
    cr_assert_eq(shell.exit_code, 1);
}

Test(builtin_cd, should_fail_if_no_home_set, .init = redirect_all_stdout_cd)
{
    shell_t shell = {0};
    char *args[] = {"cd", NULL};

    int ret = builtin_cd(&shell, args);

    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit_code, 1);
}

Test(expand_tilde, should_return_null_if_home_not_set)
{
    shell_t shell = {0};
    char *result = expand_tilde(&shell, "~/Documents");
    cr_assert_null(result);
}

Test(expand_tilde, should_return_null_if_malloc_fails)
{
    shell_t shell = {0};
    shell.env_array = malloc(sizeof(char *) * 2);
    shell.env_array[0] = strdup("HOME=/a");
    shell.env_array[1] = NULL;
    shell.env_size = 1;

    char *result = expand_tilde(&shell, "~");
    cr_assert_str_eq(result, "/a");

    free(result);
    free(shell.env_array[0]);
    free(shell.env_array);
}

Test(get_target_directory, should_return_arg_if_not_special)
{
    shell_t shell = {0};
    char *result = get_target_directory(&shell, "/usr/bin");
    cr_assert_str_eq(result, "/usr/bin");
}

Test(handle_cd_target_error, should_return_1_if_target_is_null, .init = redirect_all_stdout_cd)
{
    shell_t shell = {0};
    char *old_pwd = strdup("/home/user");
    int ret = handle_cd_target_error(&shell, NULL, old_pwd, 0);

    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit_code, 1);
}

Test(check_cd_conditions, should_fail_if_target_dir_null, .init = redirect_all_stdout_cd)
{
    shell_t shell = {0};
    int result = check_cd_conditions(&shell, NULL, strdup("/old/path"));

    cr_assert_eq(result, 1);
    cr_assert_eq(shell.exit_code, 1);
}

Test(check_cd_conditions, should_fail_if_not_a_directory, .init = redirect_all_stdout_cd)
{
    shell_t shell = {0};
    char *filename = "test_non_directory.txt";
    FILE *file = fopen(filename, "w");
    cr_assert_not_null(file);
    fclose(file);

    int result = check_cd_conditions(&shell, filename, strdup("/old/path"));

    cr_assert_eq(result, 1);
    cr_assert_eq(shell.exit_code, 1);
    remove(filename);
}

Test(check_cd_conditions, should_pass_if_directory_exists)
{
    shell_t shell = {0};

    int result = check_cd_conditions(&shell, ".", strdup("/old/path"));

    cr_assert_eq(result, 0);
}

Test(handle_cd_errors, should_fail_if_check_cd_conditions_fails, .init = redirect_all_stdout_cd)
{
    shell_t shell = {0};
    int result = handle_cd_errors(&shell, NULL, strdup("/old/path"));

    cr_assert_eq(result, 1);
}

Test(handle_cd_errors, should_fail_if_chdir_fails, .init = redirect_all_stdout_cd)
{
    shell_t shell = {0};
    int result = handle_cd_errors(&shell, "non_existing_dir", strdup("/old/path"));

    cr_assert_eq(result, 1);
    cr_assert_eq(shell.exit_code, 1);
}

Test(handle_cd_errors, should_pass_if_chdir_succeeds)
{
    shell_t shell = {0};

    int result = handle_cd_errors(&shell, ".", strdup("/old/path"));

    cr_assert_eq(result, 0);
}
