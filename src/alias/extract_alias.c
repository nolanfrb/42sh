/*
** EPITECH PROJECT, 2025
** 42sh [WSL: Ubuntu-24.04]
** File description:
** extract_alias
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "alias.h"

alias_info_t *extract_alias(char *line, alias_info_t *alias_info)
{
    regex_t regex;
    regmatch_t matches[3];
    const char *pattern = "^alias[ \t]+([a-zA-Z0-9_]+)='([^']+)'";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
        return NULL;
    if (regexec(&regex, line, 3, matches, 0) == 0) {
        alias_info->name = strndup(line + matches[1].rm_so,
            matches[1].rm_eo - matches[1].rm_so);
        alias_info->value = strndup(line + matches[2].rm_so,
            matches[2].rm_eo - matches[2].rm_so);
    }
    regfree(&regex);
    return alias_info;
}
