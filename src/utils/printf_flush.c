/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** printf_flush
*/

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

void printf_flush(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
}
