/*
** EPITECH PROJECT, 2020
** understanding
** File description:
** my_intlen
*/

#include "basics.h"

int my_intlen(int nb)
{
    int len = 1;

    if (nb < 0) nb *= -1;
    for (; nb >= 10; len++)
        nb /= 10;
    return (len);
}