/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** display_lexer
*/

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

void lexer_print_tokens(lexer_t *lexer)
{
    chain_node_t *current;
    token_t *token;

    if (lexer == NULL || lexer->tokens == NULL) {
        fprintf(stderr, "Lexer or tokens are NULL\n");
        return;
    }
    current = lexer->tokens->head;
    while (current != NULL) {
        token = (token_t *)current->data;
        if (token != NULL) {
            printf("Token type: %d, value: %s\n", token->type, token->value);
        }
        current = current->next;
    }
}
