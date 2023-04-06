/*
** EPITECH PROJECT, 2020
** 109titration_2019
** File description:
** my_swap
*/

#include "basics.h"

void my_swapi(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void my_swapf(float *a, float *b)
{
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

void my_swapd(double *a, double *b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}