/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** chain
*/

#ifndef CHAIN_H_
    #define CHAIN_H_

typedef struct chain_s chain_t;
typedef struct chain_node_s chain_node_t;
typedef struct hash_key_s hash_key_t;

struct chain_node_s {
    void *data;
    chain_node_t *next;
    chain_node_t *prev;
};

struct chain_s {
    chain_node_t *head;
    chain_node_t *tail;
    int length;
};

chain_t *chain_create(void);
void chain_iterate(chain_t *chain, void (*func)(void *));
int chain_add(chain_t *chain, void *data);
int chain_destroy(chain_t *chain);
int chain_remove(chain_t *chain, void *data);

#endif /* !CHAIN_H_ */
