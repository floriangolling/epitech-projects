/*
** EPITECH PROJECT, 2020
** PSU_tetris_2019
** File description:
** my_case
*/

#include "basics.h"

void my_lowcase(char *str)
{
    for (int e = 0; str[e]; ++e) {
        if (str[e] >= 'A' && str[e] <= 'Z')
            str[e] = str[e] + 32;
    }
}

void my_upcase(char *str)
{
    for (int e = 0; str[e]; ++e) {
        if (str[e] >= 'a' && str[e] <= 'z')
            str[e] = str[e] - 32;
    }
}