/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** line_editing
*/

#ifndef LINE_EDITING_H_
    #define LINE_EDITING_H_
    #include <termios.h>
    #include <unistd.h>
    #include <stdbool.h>
    #include "shell.h"

typedef void (*key_handler_t)(shell_t *shell, char *buffer, int *index);

typedef struct escape_mapping_s {
    int code;
    key_handler_t handler;
} escape_mapping_t;

extern const escape_mapping_t esc_mappings[];

void save_terminal_settings(void);
void restore_terminal_settings(void);

void set_non_canonical_mode(void);

bool handle_escape_sequence(shell_t *shell_info, char *buffer, int *index);
void handle_history_up(shell_t *shell, char *buffer, int *index);
void handle_history_down(shell_t *shell, char *buffer, int *index);
char *read_command_line(shell_t *shell_info, bool *had_error);

#endif /* !LINE_EDITING_H_ */
