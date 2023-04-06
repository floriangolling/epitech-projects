/*
** EPITECH PROJECT, 2019
** myprintf project
** File description:
** Convert an int to an array
*/

#include "my.h"
#include <stdlib.h>

char *ifzero(char *str)
{
    str = malloc(sizeof(char) * 2);
    str[0] = '0';
    str[1] = '\0';
    return (str);
}

char *my_nbrtoarray(int nb)
{
    int cpy_nb = nb;
    char *str;
    int n = 0;

    n = size_int(nb);
    if (nb == 0) {
        return (ifzero(str));
    } else {
        str = malloc(sizeof(char) * n + 1);
        str[n] = '\0';
        --n;
        while (cpy_nb != 0) {
            str[n] = cpy_nb % 10 + '0';
            cpy_nb = cpy_nb / 10;
            --n;
        }
        return (str);
    }
}