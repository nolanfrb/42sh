/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** utils
*/

#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

void handle_exit_status(int status)
{
    if (WTERMSIG(status) == SIGSEGV) {
        fprintf(stderr, "Segmentation fault (core dumped)\n");
    } else if (WTERMSIG(status) == SIGFPE) {
        fprintf(stderr, "Floating exception (core dumped)\n");
    }
}

void handle_command_not_found(char *command)
{
    struct stat path_stat;

    if (stat(command, &path_stat) == -1 || errno == ENOENT) {
        fprintf(stderr, "%s: Command not found.\n", command);
        return;
    }
    if (S_ISDIR(path_stat.st_mode) || !(path_stat.st_mode & S_IXUSR)) {
        fprintf(stderr, "%s: Permission denied.\n", command);
        return;
    }
    if (errno == ENOEXEC) {
        fprintf(stderr, "%s: Exec format error. Binary file not executable.\n",
            command);
        return;
    }
    fprintf(stderr, "%s: Command not found.\n", command);
}
