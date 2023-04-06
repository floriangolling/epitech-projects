/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"

int error_file(char *av)
{
    if (av[my_strlen(av) - 1] != 's' || av[my_strlen(av) - 2] != '.')
        return (84);
    return (0);
}