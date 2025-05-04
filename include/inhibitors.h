/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** inhibitors
*/

#ifndef INHIBITORS_H_
    #define INHIBITORS_H_
    #define DOUBLE_QUOTE '"'
    #define SIMPLE_QUOTE '\''
    #define BACKSLASH '\\'
    #define BACKTICK '`'
typedef enum {
    INHIBITOR_NONE,
    INHIBITOR_SIMPLE,
    INHIBITOR_DOUBLE,
    INHIBITOR_BACKSLASH
} inhibitor_type_t;

typedef struct inhibitor_s {
    char character;
    int *start;
    int end;
} inhibitor_t;

int process_inhibited_zone(
    char *cmd_line, inhibitor_t *inhibitor, word_info_t *word_info
);
bool is_inhibitor(char c);
char *process_inhibitor_sequence(char *cmd_line, int *pos);
int process_inhibitor(
    char *cmd_line, int *pos, char **combined
);
char *extract_inhibited_content(char *cmd_line, int start, int end);

#endif /* !INHIBITORS_H_ */
