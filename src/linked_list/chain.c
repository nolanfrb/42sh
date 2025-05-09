/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** chain
*/

#include <stdlib.h>
#include "chain.h"

chain_t *chain_create(void)
{
    chain_t *chain = (chain_t *)malloc(sizeof(chain_t));

    if (chain == NULL)
        return NULL;
    chain->head = NULL;
    chain->tail = NULL;
    chain->length = 0;
    return chain;
}

int chain_destroy(chain_t *chain)
{
    chain_node_t *current = chain->head;
    chain_node_t *next = NULL;

    if (chain == NULL)
        return -1;
    while (current != NULL) {
        next = current->next;
        if (current->data != NULL)
            free(current->data);
        free(current);
        current = next;
    }
    free(chain);
    return 0;
}

void chain_iterate(chain_t *chain, void (*func)(void *))
{
    chain_node_t *current = chain->tail;

    if (chain == NULL || func == NULL)
        return;
    while (current != NULL) {
        func(current->data);
        current = current->prev;
    }
}

int chain_add(chain_t *chain, void *data)
{
    chain_node_t *new_node = (chain_node_t *)malloc(sizeof(chain_node_t));

    if (chain == NULL || new_node == NULL)
        return -1;
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = chain->tail;
    if (chain->tail != NULL)
        chain->tail->next = new_node;
    else
        chain->head = new_node;
    chain->tail = new_node;
    chain->length++;
    return 0;
}

static void relink_chain(chain_t *chain, chain_node_t *node)
{
    if (node == chain->head)
        chain->head = node->next;
    if (node == chain->tail)
        chain->tail = node->prev;
    if (node->prev != NULL)
        node->prev->next = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
}

int chain_remove(chain_t *chain, void *data)
{
    chain_node_t *current = chain->head;

    if (chain == NULL || chain->head == NULL)
        return -1;
    while (current && current->data != data) {
        current = current->next;
    }
    if (current == NULL)
        return -1;
    relink_chain(chain, current);
    free(current);
    chain->length--;
    return 0;
}
