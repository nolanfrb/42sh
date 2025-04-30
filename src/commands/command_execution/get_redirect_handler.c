/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** get_redirect_handler
*/

#include "ast.h"
#include "redirect_cmd.h"

void (*get_redirect_handler(redirect_type_t type))(char *)
{
    static void (*handlers[])(char *) = {
        [REDIR_NONE] = NULL,
        [REDIR_OUT] = handle_output_redirection,
        [REDIR_APPEND] = handle_append_redirection,
        [REDIR_IN] = handle_input_redirection,
        [REDIR_HEREDOC] = handle_heredoc_redirection,
    };

    return (type >= REDIR_NONE && type <= REDIR_HEREDOC) ?
        handlers[type] : NULL;
}
