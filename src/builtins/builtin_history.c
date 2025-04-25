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
#include "env.h"
#include <time.h>

history_t *init_history(void)
{
    history_t *hist = malloc(sizeof(history_t));

    if (!hist)
        return NULL;
    hist->entries = malloc(sizeof(history_entry_t) * INITIAL_HISTORY_CAPACITY);
    if (!hist->entries) {
        free(hist);
        return NULL;
    }
    hist->count = 0;
    hist->capacity = INITIAL_HISTORY_CAPACITY;
    return hist;
}

static bool realloc_history_entries(history_t *hist)
{
    history_entry_t *new_entries = realloc(hist->entries,
        hist->capacity * 2 * sizeof(history_entry_t));

    if (!new_entries)
        return false;
    hist->capacity *= 2;
    hist->entries = new_entries;
    return true;
}

static char *get_current_time_str(void)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char *time_str = malloc(6);

    if (!tm_info || !time_str)
        return NULL;
    strftime(time_str, 6, "%H:%M", tm_info);
    return time_str;
}

void history_add(history_t *hist, const char *line)
{
    char *timestamp;

    if (!line || !hist)
        return;
    if (hist->count >= hist->capacity) {
        if (!realloc_history_entries(hist))
            return;
    }
    timestamp = get_current_time_str();
    if (!timestamp)
        return;
    hist->entries[hist->count].command = strdup(line);
    hist->entries[hist->count].timestamp = timestamp;
    if (hist->entries[hist->count].command != NULL &&
        hist->entries[hist->count].timestamp != NULL)
        hist->count++;
}

static char *resolve_by_prefix(history_t *hist, const char *prefix)
{
    size_t len = strlen(prefix);

    for (int i = hist->count - 1; i >= 0; i--) {
        if (strncmp(hist->entries[i].command, prefix, len) == 0)
            return hist->entries[i].command;
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
        return hist->entries[hist->count - 1].command;
    }
    if (input[1] >= '0' && input[1] <= '9') {
        idx = atoi(&input[1]);
        if (idx <= 0 || idx > hist->count)
            return NULL;
        return hist->entries[idx - 1].command;
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
        printf("%6d\t%s\t%s\n",
            i + 1,
            shell->history->entries[i].timestamp,
            shell->history->entries[i].command);
    }
    return 0;
}
