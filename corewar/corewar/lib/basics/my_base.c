/*
** EPITECH PROJECT, 2020
** understanding
** File description:
** my_putbase
*/

#include "basics.h"

int my_baselen(int nb, int len_base)
{
    int len = 0;

    for (len = 0; nb > 0; len++)
        nb /= len_base;
    return (len);
}

void my_putbase(int nb, char *base, int len_base)
{
    int mod = 0;
    static int inc = 0;

    inc++;
    if (base == NULL)
        return;
    if (nb > 0) {
        mod = nb % len_base;
        nb /= len_base;
        my_putbase(nb, base, len_base);
        my_putchar(base[mod]);
    } else if (inc == 1)
        my_putchar(base[0]);
}

char *my_ch_base(int nb, char *base)
{
    int mod = 0;
    int e = 0;
    int len_base = my_strlen(base);
    char *result = malloc(sizeof(char) * (my_baselen(nb, len_base) + 1));

    if (result == NULL)
        return (NULL);
    for (e = 0; nb > 0; e++) {
        mod = nb % len_base;
        nb /= len_base;
        result[e] = base[mod];
    }
    result[e] = '\0';
    my_revstr(result);
    return (result);
}