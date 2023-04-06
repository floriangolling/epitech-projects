/*
** EPITECH PROJECT, 2019
** my_strdup
** File description:
** my_strdup
*/

#include "my.h"
#include <stdlib.h>

char *my_strdup(char *str)
{
    char *s;

    if (!(s = malloc(my_strlen(str) + 1)))
        return (0);
    my_strcpy(s, str);
    return (s);
}