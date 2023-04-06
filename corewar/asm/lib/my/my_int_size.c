/*
** EPITECH PROJECT, 2019
** myprintf project
** File description:
** Convert an int to an array
*/

#include "my.h"

int size_int(int nb)
{
    int n = nb;
    int i = 1;

    while (n > 9) {
        n = n / 10;
        ++i;
    }
    return (i);
}