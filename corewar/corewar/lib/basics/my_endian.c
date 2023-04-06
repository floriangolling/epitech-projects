/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** my_endian
*/

#include "basics.h"

void big_endian(int *nb)
{
    int ref = 1073741824;
    int inv = 1;
    int new = 0;

    for (; ref > 0; ref = ref >> 1, inv = inv << 1) {
        if (*nb & ref)
            new |= inv;
    }
    *nb = new;
}