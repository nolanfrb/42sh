/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** lexer
*/

#ifndef LEXER_H_
    #define LEXER_H_
    #include <stdbool.h>

extern const char *SPECIAL_TOKENS[];
typedef struct word_info_s word_info_t;

struct word_info_s {
    int start;
    char **words;
    int word_idx;
};

char **lexer(char *cmd_line);
int handle_delimiter(char *cmd_line, int *i, word_info_t *word_info,
    char *delimiters);
bool is_delimiter(char character, char *delimiters);
char *extract_word(char *input, int start, int len);
int handle_special_token(char *cmd_line, int *i,
    word_info_t *word_info);
int check_special_token(const char *cmd_line, int pos);
int count_words(char *str, char *delimiters);

#endif /* !LEXER_H_ */
