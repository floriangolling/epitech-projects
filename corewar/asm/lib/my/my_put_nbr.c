/*
** EPITECH PROJECT, 2019
** myputnbr
** File description:
** display a number enter in parameter
*/

#include "my.h"

int my_put_nbr(int nb)
{
    int subs = 0;

    if (nb < 0) {
        nb = nb * -1;
        my_putchar('-');
    }
    if (nb >= 10) {
        subs = nb % 10;
        nb = nb - subs;
        nb = nb / 10;
        my_put_nbr(nb);
        my_putchar(subs + 48);
    } else {
            nb = nb % 10;
            my_putchar(nb + 48);
    }
}
