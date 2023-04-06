/*
** EPITECH PROJECT, 2020
** n4s_package
** File description:
** my_putfloat
*/

#include "basics.h"

static void negative_number(float *nb)
{
    if (*nb < 0) {
        write(1, "-", 1);
        *nb *= -1;
    }
}

void put_integer_of_float(int nb)
{
    int modulo = 0;

    if (nb >= 10) {
        modulo = (nb % 10);
        nb = (nb - modulo) / 10;
        put_integer_of_float(nb);
        my_putchar(48 + modulo);
    } else if (nb >= 0)
        my_putchar(48 + nb % 10);
}

void my_putfloat(float nb)
{
    negative_number(&nb);
    put_integer_of_float(nb);
    nb = (nb - (int)nb) * 10000;
    write(1, ".", 1);
    put_integer_of_float(nb);
}
