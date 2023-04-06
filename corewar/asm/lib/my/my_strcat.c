/*
** EPITECH PROJECT, 2019
** my_strcat
** File description:
** concatenate two strings
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int j = 0;

    j = my_strlen(dest);
    while (src[i] != '\0') {
        dest[j + i] = src[i];
        i++;
    }
    dest[j + i] = '\0';
    return (dest);
}
