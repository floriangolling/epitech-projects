/*
** EPITECH PROJECT, 2019
** my_strncat
** File description:
** concatenate two strings
*/

#include "my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int i = 0;
    int j = 0;

    j = my_strlen(dest);
    while (i <= nb - 1) {
        dest[j + i] = src[i];
        i++;
    }
    dest[j + i] = '\0';
}
