#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell.h"
#include "builtins.h"

#define free_shell mocked_free_shell
#define exit mocked_exit


void redirect_all_stdout_exit(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

void mocked_free_shell(shell_t *shell)
{
    (void)shell;
}

void mocked_exit(int status)
{
    _exit(status);
}

// Test(builtin_exit, should_exit_with_zero_if_no_argument, .init = redirect_all_stdout_exit)
// {
//     pid_t pid = fork();
//     cr_assert_neq(pid, -1, "fork() failed");

//     if (pid == 0) {
//         shell_t shell = {0};
//         char *args[] = {"exit", NULL};
//         builtin_exit(&shell, args);
//     } else {
//         int status;
//         waitpid(pid, &status, 0);

//         cr_assert(WIFEXITED(status), "Child did not exit normally");
//         cr_assert_eq(WEXITSTATUS(status), 0, "Expected exit code 0");
//     }
// }

// Test(builtin_exit, should_exit_with_given_code, .init = redirect_all_stdout_exit)
// {
//     pid_t pid = fork();
//     cr_assert_neq(pid, -1, "fork() failed");

//     if (pid == 0) {
//         shell_t shell = {0};
//         char *args[] = {"exit", "42", NULL};
//         builtin_exit(&shell, args);
//     } else {
//         int status;
//         waitpid(pid, &status, 0);

//         cr_assert(WIFEXITED(status), "Child did not exit normally");
//         cr_assert_eq(WEXITSTATUS(status), 42, "Expected exit code 42");
//     }
// }