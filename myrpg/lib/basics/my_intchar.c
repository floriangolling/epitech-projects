/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** my_intchar
*/

#include "basics.h"

static int nb_length(int nb)
{
    int e = 1;

    if (nb < 0) {
        nb *= -1;
        e++;
    }
    for (; nb >= 10; e++)
        nb /= 10;
    return (e);
}

char *my_intchar(int nb)
{
    int length = nb_length(nb);
    char *nb_char = malloc(sizeof(char) * (length + 1));
    int inc_nbc = 0;
    int neg = 0;

    if (nb < 0) {
        neg = 1;
        nb *= -1;
    }
    for (int i = 0; i < length; i++, inc_nbc++) {
        nb_char[inc_nbc] = (nb % 10) + 48;
        nb /= 10;
    }
    if (neg == 1)
        nb_char[length - 1] = '-';
    nb_char[inc_nbc] = '\0';
    my_reverse(nb_char);
    return (nb_char);
}