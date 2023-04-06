/*
** EPITECH PROJECT, 2019
** lib
** File description:
** Calcul the mimum of three numbers
*/

#include "my.h"

int my_min(int first, int second, int third)
{
    int temp_one;

    if (first < second || first == second)
        temp_one = first;
    else
        temp_one = second;
    if (temp_one < third || temp_one == third)
        return (temp_one);
    else
        return (third);
}