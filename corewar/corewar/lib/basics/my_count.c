/*
** EPITECH PROJECT, 2020
** PSU_navy_2019
** File description:
** my_count
*/

#include "basics.h"

int my_count_co(char *str, char character)
{
    int nb_c = 0;

    for (int e = 0; str[e]; ++e)
        if (str[e] == character)
            ++nb_c;
    return (nb_c);
}

int my_count_coo(char **str, char character)
{
    int nb_c = 0;

    for (int e = 0; str[e]; ++e)
        for (int i = 0; str[e][i]; ++i)
            if (str[e][i] == character)
                ++nb_c;
    return (nb_c);
}

int my_count_too(char **str, char open, char close)
{
    int nb_c = 0;

    for (int e = 0; str[e]; ++e)
        for (int i = 0; str[e][i]; ++i)
            if (str[e][i] >= open && str[e][i] <= close)
                ++nb_c;
    return (nb_c);
}