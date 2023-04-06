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

char *my_itoa(int nb)
{
    int length = nb_length(nb);
    char *nb_char = malloc(sizeof(char) * (length + 1));
    int inc_nbc = 0;
    int neg = 0;

    if (!nb_char) return (NULL);
    if (nb < 0) {
        neg = 1;
        nb *= -1;
    }
    for (int i = 0; i < length; i++, inc_nbc++, nb /= 10)
        nb_char[inc_nbc] = (nb % 10) + 48;
    if (neg == 1)
        nb_char[length - 1] = '-';
    nb_char[inc_nbc] = '\0';
    my_revstr(nb_char);
    return (nb_char);
}

char *nm_itoa(char in[10], int nb)
{
    int length = nb_length(nb);
    int inc_nbc = 0;
    int neg = 0;

    if (length > 9) {
        in[0] = '1';
        in[1] = '\0';
        return (in);
    }
    if (nb < 0) {
        neg = 1;
        nb *= -1;
    }
    for (int i = 0; i < length; i++, inc_nbc++, nb /= 10)
        in[inc_nbc] = (nb % 10) + 48;
    if (neg == 1)
        in[length - 1] = '-';
    in[inc_nbc] = '\0';
    my_revstr(in);
    return (in);
}