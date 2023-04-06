/*
** EPITECH PROJECT, 2020
** my_occur
** File description:
** occurence
*/

#include "basics.h"

int my_occur(char *str, char element)
{
    int inc = 0;
    int occurence = 0;

    for (inc = 0; str[inc]; inc++)
        if (str[inc] == element)
            occurence++;
    return (occurence);
}