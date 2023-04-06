/*
** EPITECH PROJECT, 2020
** minishell_no_leak
** File description:
** my_free
*/

#include "basics.h"

void my_free(char *one, char *two, char *three, int release)
{
    if (release - 5 >= 0) {
        release -= 5;
        free(three);
    }
    if (release - 3 >= 0) {
        release -= 3;
        free(two);
    }
    if (release - 1 >= 0) {
        release -= 1;
        free(one);
    }
}

void my_free_oo(char **oo)
{
    for (int e = 0; oo[e] != NULL; e++)
        free(oo[e]);
    free(oo);
}

void my_free_typoo(void **oo)
{
    for (int e = 0; oo[e] != NULL; e++)
        free(oo[e]);
    free(oo);
}