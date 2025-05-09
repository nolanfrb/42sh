/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** strcat
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void free_memory(char *s1, char *s2)
{
    if (s1)
        free(s1);
    if (s2)
        free(s2);
}

/**
 * @brief Concatenate two strings
 * @param dest First string
 * @param str Second string
 * @return Newly allocated string with concatenated result
 */
char *my_strcat(char *dest, char const *str)
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

char *safe_strcat(char *s1, char *s2)
{
    char *result;
    size_t len1 = (s1) ? strlen(s1) : 0;
    size_t len2 = (s2) ? strlen(s2) : 0;

    if (!s1 && !s2)
        return NULL;
    if (!s1)
        return s2;
    if (!s2)
        return s1;
    result = malloc(len1 + len2 + 1);
    if (!result) {
        free_memory(s1, s2);
        return NULL;
    }
    strcpy(result, s1);
    strcat(result, s2);
    free_memory(s1, s2);
    return result;
}
