/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** ui
*/

#include "shell.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

static char *getstring(void)
{
    char *input = NULL;
    size_t size = 0;
    size_t capacity = 1;
    int ch;
    input = malloc(capacity);
    if (!input)
        return NULL;
    nocbreak();
    echo();
    ch = getch();
    while (ch != '\n' && ch != '\r') {
        if (size + 1 >= capacity) {
            capacity += 1;
            char *new_input = realloc(input, capacity);
            if (!new_input) {
                free(input);
                return NULL;
            }
            input = new_input;
        }
        input[size++] = ch;
        ch = getch();
    }
    input[size] = '\0';
    char *result = realloc(input, size + 1);
    if (!result) {
        return input;
    }
    return result;
}

int user_interface(void)
{   
    char *cmd_line;
    
    initscr();
    while (true) {
        move(LINES - 1, 0);
        addch('$');
        addch('>');
        refresh();
        cmd_line = getstring();
        if (!cmd_line) {
            endwin();
            return 84;
        }
        mvprintw(LINES - 2, 0, "You Entered: %s", cmd_line);
        refresh();
        free(cmd_line);
        //clear();
    }
    
    endwin();
    return 0;
}