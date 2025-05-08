/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** lexer
*/

#ifndef LEXER_H_
    #define LEXER_H_
    #include <stdbool.h>
    #include "chain.h"
    #include "inhibitors.h"
    #include "shell.h"

extern const char *SPECIAL_TOKENS[];

typedef enum {
    TOKEN_WORD,
    TOKEN_VARIABLE,
    TOKEN_PIPE,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_SEMICOLON,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_APPEND_OUT,
    TOKEN_HEREDOC,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END
} token_type_t;

typedef struct {
    token_type_t type;
    char *value;
} token_t;

typedef struct {
    chain_t *tokens;
    token_t *current;
    char *input;
    int start;
    int pos;
    int token_count;
    quote_state_t inhibitor_state;
    shell_t *shell;
} lexer_t;

typedef struct {
    char symbol;
    int (*handler)(lexer_t *);
} special_char_handler_t;

extern const special_char_handler_t SPECIAL_CHARS[];
char **build_tokens(const char *input, shell_t *shell);

lexer_t *lexer_init(const char *input, shell_t *shell);
void free_lexer(lexer_t *lexer);
lexer_t *lexer_create(const char *input, shell_t *shell);
int lexer_tokenize(lexer_t *lexer);
char **lexer_to_strings(lexer_t *lexer);

int lexer_add_token(lexer_t *lexer, token_type_t type, const char *value);
int lexer_token_count(lexer_t *lexer);

void lexer_print_tokens(lexer_t *lexer);

// handling special characters
int handle_word(lexer_t *lexer);
int handle_pipe(lexer_t *lexer);
int handle_and(lexer_t *lexer);
int handle_redirect_in(lexer_t *lexer);
int handle_redirect_out(lexer_t *lexer);
int handle_semicolon(lexer_t *lexer);
int handle_left_parenthesis(lexer_t *lexer);
int handle_right_parenthesis(lexer_t *lexer);
int handle_variable(lexer_t *lexer, shell_t *shell);

char *extract_variable_name(char *input, int start, int *end);

// Utility functions
bool is_special_char(char *str);
bool is_whitespace(char c);

#endif /* !LEXER_H_ */
