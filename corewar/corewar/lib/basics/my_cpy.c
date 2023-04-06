/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_cpy
*/

#include "basics.h"

char *my_cpy(char *str, int release)
{
    int e = 0;
    char *cpy = malloc(sizeof(char) * (my_strlen(str) + 1));

    if (cpy == NULL)
        return (NULL);
    for (e = 0; str[e]; e++)
        cpy[e] = str[e];
    cpy[e] = '\0';
    my_free(str, NULL, NULL, release);
    return (cpy);
}

char *my_cpy_st(char *str, char start, int release)
{
    int inc = 0;
    int inc_cpy = 0;
    char *cpy = malloc(sizeof(char) * (my_stlen(str, start, 0) + 1));

    if (cpy == NULL)
        return (NULL);
    for (; str[inc] && str[inc] != start; inc++);
    inc++;
    for (; str[inc]; inc++)
        cpy[inc_cpy++] = str[inc];
    cpy[inc_cpy] = '\0';
    my_free(str, NULL, NULL, release);
    return (cpy);
}

char *my_cpy_lim(char *original, char lim, int release)
{
    int e = 0;
    char *copy = malloc(sizeof(char) * (my_limlen(original, lim, 0) + 1));

    for (e = 0; original[e] != '\0' && original[e] != lim; e++)
        copy[e] = original[e];
    copy[e] = '\0';
    my_free(original, NULL, NULL, release);
    return (copy);
}

char **my_oocpy(char **oo)
{
    int e = 0;
    int i = 0;
    char **cpy = malloc(sizeof(char *) * (my_oolen(oo) + 1));

    if (cpy == NULL)
        return (NULL);
    for (e = 0; oo[e] != NULL; e++) {
        cpy[e] = malloc(sizeof(char) * (my_strlen(oo[e]) + 1));
        if (cpy[e] == NULL)
            return (NULL);
        for (i = 0; oo[e][i] != '\0'; i++)
            cpy[e][i] = oo[e][i];
        cpy[e][i] = '\0';
    }
    cpy[e] = NULL;
    return (cpy);
}