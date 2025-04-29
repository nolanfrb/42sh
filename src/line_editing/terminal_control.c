/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** terminal_control
*/

#include <termios.h>
#include <unistd.h>
#include "line_editing.h"

static struct termios saved;

void save_terminal_settings(void)
{
    tcgetattr(STDIN_FILENO, &saved);
}

void restore_terminal_settings(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &saved);
}

void set_non_canonical_mode(void)
{
    struct termios t;

    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    t.c_cc[VMIN] = 1;
    t.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void handle_escape_sequence(shell_t *shell_info)
{
    char seq[2];

    if (read(STDIN_FILENO, seq, 2) != 2)
        return;
    for (int i = 0; esc_mappings[i].handler != NULL; i++) {
        if (seq[1] == esc_mappings[i].code) {
            esc_mappings[i].handler(shell_info);
            return;
        }
    }
}
