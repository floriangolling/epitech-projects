/*
** EPITECH PROJECT, 2019
** my_revstr.c
** File description:
** my_revstr
*/

#include "basics.h"

void my_revstr(char *str)
{
    int a = 0;
    int o = my_strlen(str) - 1;
    int middle = (o % 2 == 0) ? o / 2 : o / 2 + 1;

    for (; a != middle; a++, o--) {
        str[a] ^= str[o];
        str[o] ^= str[a];
        str[a] ^= str[o];
    }
}