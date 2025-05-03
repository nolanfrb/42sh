/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** escape_mappings
*/

#include "line_editing.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

const escape_mapping_t esc_mappings[] = {
    {65, handle_history_up},
    {66, handle_history_down},
    {0, NULL}
};
