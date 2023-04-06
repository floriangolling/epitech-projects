/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** my_strlen
*/

#include "basics.h"

int my_strlen(char const *str)
{
    int i = 0;

    for (i = 0; str[i]; i++);
    return (i);
}

int my_limlen(char *str, char lim, int release)
{
    int length = 0;

    for (length = 0; str[length] != '\0' && str[length] != lim; length++);
    my_free(str, NULL, NULL, release);
    return (length);
}

int my_nlimlen(char *str, char lim, int occurence, int release)
{
    int nb_lim = 0;
    int length = 0;

    for (length = 0; str[length] != '\0' && nb_lim < occurence; length++)
        if (str[length] == lim)
            nb_lim++;
    my_free(str, NULL, NULL, release);
    return (length);
}

int my_stlen(char *str, char start, int release)
{
    int e = 0;
    int length = 0;

    for (e = 0; str[e] && str[e] != start; e++);
    for (; str[e]; e++, length++);
    my_free(str, NULL, NULL, release);
    return (length);
}

int my_oolen(char **oo)
{
    int length = 0;

    for (; oo[length] != NULL; length++);
    return (length);
}