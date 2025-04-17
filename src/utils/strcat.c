/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** strcat
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Concatenate two strings
 * @param dest First string
 * @param str Second string
 * @return Newly allocated string with concatenated result
 */
char *my_strcat(char *dest, char *str)
{
    int i = 0;
    int len = strlen(dest);
    char *result = malloc(sizeof(char) * (len + strlen(str) + 1));

    if (!result)
        return NULL;
    strcpy(result, dest);
    while (str[i] != '\0') {
        result[len + i] = str[i];
        i++;
    }
    result[len + i] = '\0';
    return result;
}
