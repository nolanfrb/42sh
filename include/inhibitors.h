/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** inhibitors
*/

#ifndef INHIBITORS_H_
    #define INHIBITORS_H_
    #include <stdbool.h>
    #define DOUBLE_QUOTE '"'
    #define SIMPLE_QUOTE '\''
    #define BACKSLASH '\\'
    #define BACKTICK '`'

typedef enum {
    STATE_NORMAL = 0,
    STATE_SINGLE_QUOTE,
    STATE_DOUBLE_QUOTE,
    STATE_ESCAPE
} quote_state_t;

typedef struct inhibitor_s {
    char character;
    int *start;
    int end;
} inhibitor_t;

bool is_inhibitor(char c);
char *process_inhibitor_sequence(char *cmd_line, int *pos);
int process_inhibitor(
    char *cmd_line, int *pos, char **combined
);
char *extract_inhibited_content(char *cmd_line, int start, int end);

#endif /* !INHIBITORS_H_ */
