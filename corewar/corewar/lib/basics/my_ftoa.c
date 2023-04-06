/*
** EPITECH PROJECT, 2020
** n4s_package
** File description:
** my_ftoa
*/

#include "basics.h"

static void negative_number(char *number, float *nb, int *ic_n)
{
    if (*nb < 0) {
        number[*ic_n] = '-';
        ++*ic_n;
        *nb *= -1;
    }
}

void take_digit_before_dot(char *number, int nb, int *ic_n)
{
    int modulo = 0;

    if (nb >= 10) {
        modulo = (nb % 10);
        nb = (nb - modulo) / 10;
        take_digit_before_dot(number, nb, ic_n);
        number[*ic_n] = modulo + 48;
        ++*ic_n;
    } else if (nb >= 0) {
        number[*ic_n] = 48 + nb % 10;
        ++*ic_n;
    }
}

void take_digit_after_dot(char *number, float decimal, int *ic_n, int i)
{
    int modulo = 0;

    if (i < 4) {
        decimal *= 10;
        modulo = (int)decimal % 10;
        number[*ic_n] = modulo + 48;
        ++*ic_n;
        ++i;
        take_digit_after_dot(number, decimal, ic_n, i);
    }
}

char *my_ftoa(float nb)
{
    int ic_n = 0;
    int len = my_intlen((int)nb);
    char *number = malloc(len + 7);

    if (!number) return (NULL);
    negative_number(number, &nb, &ic_n);
    take_digit_before_dot(number, (int)nb, &ic_n);
    number[ic_n++] = '.';
    take_digit_after_dot(number, nb, &ic_n, 0);
    number[ic_n] = '\0';
    return (number);
}

char *nm_ftoa(char *number, float nb)
{
    int ic_n = 0;
    int len = my_intlen((int)nb);

    if (len > 10) return (errorn("nm_float: too large number\n"));
    negative_number(number, &nb, &ic_n);
    take_digit_before_dot(number, (int)nb, &ic_n);
    number[ic_n++] = '.';
    take_digit_after_dot(number, nb, &ic_n, 0);
    number[ic_n++] = '\n';
    number[ic_n] = '\0';
    return (number);
}