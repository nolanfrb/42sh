/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_history
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "builtins.h"

history_t *init_history(void)
{
    history_t *hist = malloc(sizeof(history_t));

    if (!hist)
        return NULL;
    hist->entries = malloc(sizeof(char *) * INITIAL_HISTORY_CAPACITY);
    if (!hist->entries)
        return NULL;
    hist->count = 0;
    hist->capacity = INITIAL_HISTORY_CAPACITY;
    return hist;
}

static bool realloc_history_entries(history_t *hist)
{
    char **new_entries = realloc(hist->entries,
        hist->capacity * 2 * sizeof(char *));

    if (!new_entries)
        return false;
    hist->capacity *= 2;
    hist->entries = new_entries;
    return true;
}

void history_add(history_t *hist, const char *line)
{
    if (!line || !hist)
        return;
    if (hist->count >= hist->capacity) {
        if (!realloc_history_entries(hist))
            return;
    }
    hist->entries[hist->count] = strdup(line);
    if (hist->entries[hist->count])
        hist->count++;
}

static char *resolve_by_prefix(history_t *hist, const char *prefix)
{
    size_t len = strlen(prefix);

    for (int i = hist->count - 1; i >= 0; i--) {
        if (strncmp(hist->entries[i], prefix, len) == 0)
            return hist->entries[i];
    }
    return NULL;
}

char *history_resolve(history_t *hist, const char *input)
{
    int idx;

    if (!hist || !input || input[0] != '!')
        return NULL;
    if (strcmp(input, "!!") == 0) {
        if (hist->count == 0)
            return NULL;
        return hist->entries[hist->count - 1];
    }
    if (input[1] >= '0' && input[1] <= '9') {
        idx = atoi(&input[1]);
        if (idx <= 0 || idx > hist->count)
            return NULL;
        return hist->entries[idx - 1];
    }
    return resolve_by_prefix(hist, input + 1);
}

int handle_history_error(const char *input)
{
    if (!input)
        return 1;
    fprintf(stderr, "%s: Event not found.\n", input);
    return 1;
}

int builtin_history(shell_t *shell, char **args)
{
    (void)args;
    if (!shell || !shell->history)
        return 0;
    for (int i = 0; i < shell->history->count; i++) {
        printf("%d  %s\n", i + 1, shell->history->entries[i]);
    }
    return 0;
}
