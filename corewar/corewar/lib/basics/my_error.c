/*
** EPITECH PROJECT, 2020
** 109titration_2019
** File description:
** my_error
*/

#include "basics.h"

int error(char *str)
{
    write(2, str, my_strlen(str));
    return (1);
}

int info(char *str, int output, int return_value)
{
    write(output, str, my_strlen(str));
    return (return_value);
}

int errorc(char *str)
{
    write(2, str, my_strlen(str));
    return (-1);
}

int errorm(char *str)
{
    write(2, str, my_strlen(str));
    return (84);
}

void *errorn(char *str)
{
    write(2, str, my_strlen(str));
    return (NULL);
}