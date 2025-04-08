#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "shell.h"
#include "command.h"

Test(execute_command, successful_command, .init = cr_redirect_stdout)
{
    // Setup test environment
    ast_node_t node;
    shell_t shell_var;
    char *argv[] = {"/bin/echo", "Hello World", NULL};
    char *env[] = {NULL};

    // Initialize node
    node.type = NODE_COMMAND;
    node.data.command.argv = argv;
    
    // Initialize shell
    shell_var.env = env;

    // Execute command
    int exit_code = execute_command(&node, &shell_var);
    
    // Verify output
    cr_assert_stdout_eq_str("Hello World\n", "Command output should match expected");
    cr_assert_eq(exit_code, 0, "Exit code should be 0 for successful command");
}
