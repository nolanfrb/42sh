/*
** EPITECH PROJECT, 2025
** clonerepo [WSL: Ubuntu-24.04]
** File description:
** test_main
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"
#include <stdio.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}
