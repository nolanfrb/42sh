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

typedef enum {
    LEXER_NORMAL,
    LEXER_INHIBITOR,
    LEXER_VARIABLE,
} lexer_state_t;

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
    lexer_state_t state;
    quote_state_t inhibitor_state;
    shell_t *shell;
    char *concat_buffer;
} lexer_t;

typedef struct {
    char symbol;
    int (*handler)(lexer_t *);
} special_char_handler_t;

const special_char_handler_t *get_special_chars(void);

extern const special_char_handler_t special_chars[];
char **build_tokens(const char *input, shell_t *shell);
void lexer_destroy(lexer_t *lexer);

lexer_t *lexer_init(const char *input, shell_t *shell);
void free_lexer(lexer_t *lexer);
lexer_t *lexer_create(const char *input, shell_t *shell);
int lexer_tokenize(lexer_t *lexer);
char **lexer_to_strings(lexer_t *lexer);

int lexer_add_token(lexer_t *lexer, token_type_t type, const char *value);

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
int handle_special_char(lexer_t *lexer);

// Handling Variables
int handle_variable(lexer_t *lexer, shell_t *shell);
int process_variable_value(
    lexer_t *lexer, char *var_value, int end, int is_concat
);
char *get_current_word_part(lexer_t *lexer);
char *extract_variable_name(char *input, int start, int *end);

// Handling Inhibitors
int handle_inhibitor(lexer_t *lexer, char c);

int process_char(lexer_t *lexer);

// Utility functions
bool is_special_char(char *str);
bool is_whitespace(char c);

#endif /* !LEXER_H_ */
