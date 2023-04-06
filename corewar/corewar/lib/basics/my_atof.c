/*
** EPITECH PROJECT, 2020
** 109titration_2019
** File description:
** my_atof
*/

#include "basics.h"

static int get_symbol(int *i, char *str)
{
    int n = 0;

    for (; str[*i] == '-' || str[*i] == '+'; ++*i)
        if (str[*i] == '-')
            ++n;
    if (!(n % 2) || !n)
        return (1);
    else if (n % 2)
        return (-1);
}

static double get_scale(int i, char *str)
{
    double scale = 0.1;

    for (; str[i] && my_isnum(str[i]); ++i)
        scale *= 10.0;
    return (scale);
}

float my_atof(char *str, int release)
{
    int i = 0;
    float nb = 0;
    int symbol = get_symbol(&i, str);
    double scale = get_scale(i, str);

    for (; str[i] && my_isnum(str[i]); ++i, scale *= 0.1)
        nb = nb + (str[i] - 48) * scale;
    if (str[i++] != '.')
        return (my_free(str, NULL, NULL, release), nb * symbol);
    for (scale = 0.1; str[i] && my_isnum(str[i]); ++i, scale *= 0.1)
        nb = nb + (str[i] - 48) * scale;
    return (my_free(str, NULL, NULL, release), nb * symbol);
}