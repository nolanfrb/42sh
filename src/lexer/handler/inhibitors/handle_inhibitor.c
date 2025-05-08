/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** inhibitors
*/

#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "inhibitors.h"
#include <stdio.h>
#include "utils.h"

/**
 * @brief Gère le début ou la fin d'une zone entre guillemets
 * @param lexer Structure lexer
 * @return 0 si succès, -1 en cas d'erreur
 */
static int handle_quote_boundary(lexer_t *lexer)
{
    if (lexer->start != lexer->pos && handle_word(lexer) != 0)
        return -1;
    if (lexer->inhibitor_state != STATE_NORMAL)
        lexer->state = LEXER_INHIBITOR;
    lexer->pos++;
    lexer->start = lexer->pos;
    return 0;
}

/**
 * @brief Met à jour l'état de l'inhibiteur pour les guillemets doubles
 * @param lexer Structure lexer
 * @return 0 si succès, -1 en cas d'erreur
 */
static int handle_double_quote(lexer_t *lexer)
{
    if (lexer->inhibitor_state == STATE_NORMAL) {
        lexer->inhibitor_state = STATE_DOUBLE_QUOTE;
    } else if (lexer->inhibitor_state == STATE_DOUBLE_QUOTE) {
        lexer->inhibitor_state = STATE_NORMAL;
    }
    return handle_quote_boundary(lexer);
}

/**
 * @brief Met à jour l'état de l'inhibiteur pour les guillemets simples
 * @param lexer Structure lexer
 * @return 0 si succès, -1 en cas d'erreur
 */
static int handle_single_quote(lexer_t *lexer)
{
    if (lexer->inhibitor_state == STATE_NORMAL) {
        lexer->inhibitor_state = STATE_SINGLE_QUOTE;
    } else if (lexer->inhibitor_state == STATE_SINGLE_QUOTE) {
        lexer->inhibitor_state = STATE_NORMAL;
    }
    return handle_quote_boundary(lexer);
}

/**
 * @brief Gère l'échappement avec backslash
 * @param lexer Structure lexer
 * @return 0 si succès
 */
static int handle_backslash(lexer_t *lexer)
{
    if (lexer->input[lexer->pos + 1] == '\0')
        return 0;
    lexer->pos += 2;
    return 0;
}

/**
 * @brief Fonction principale de gestion des inhibiteurs
 * @param lexer Structure lexer
 * @param c Caractère courant
 * @return 0 si succès, -1 en cas d'erreur
 */
int handle_inhibitor(lexer_t *lexer, char c)
{
    switch (c) {
        case BACKSLASH:
            return handle_backslash(lexer);
        case DOUBLE_QUOTE:
            return handle_double_quote(lexer);
        case SIMPLE_QUOTE:
            return handle_single_quote(lexer);
        default:
            return 0;
    }
}
