/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_ooto
*/

#include "basics.h"

char *my_ooto(char **oo, char ramification)
{
    char *o;
    int inc = 0;
    int length = 0;

    for (int e = 0; oo[e] != NULL; e++)
        length += my_strlen(oo[e]) + 1;
    o = malloc(sizeof(char) * (length + 1));
    if (o == NULL)
        return (NULL);
    for (int e = 0; oo[e] != NULL; e++) {
        for (int i = 0; oo[e][i] != '\0'; i++) {
            o[inc++] = oo[e][i];
        }
        o[inc++] = ramification;
    }
    o[inc] = '\0';
    return (o);
}