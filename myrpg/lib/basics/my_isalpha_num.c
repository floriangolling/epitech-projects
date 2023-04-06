/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_isalpha_num
*/

#include "basics.h"

int my_isalpha_num(char *str)
{
    int i = 0;

    for (i = 0; str[i]; i++) {
        if ((str[i] >= '0' && str[i] <= '9') || str[i] == ' ')
            continue;
        else if ((str[i] >= 'A' && str[i] <= 'Z') ||
                (str[i] >= 'a' && str[i] <= 'z'))
            continue;
        else
            return (-1);
    }
    return (0);
}

int my_isin(char *str, char open, char close, int release)
{
    int e = 0;

    for (e = 0; str[e] && str[e] >= open && str[e] <= close; ++e);
    if (str[e] == '\0') {
        my_free(str, NULL, NULL, release);
        return (1);
    }
    my_free(str, NULL, NULL, release);
    return (0);
}

int my_isnum(char character)
{
    if (character >= '0' && character <= '9')
        return (1);
    return (0);
}

int my_isalpha(char character, char open, char close)
{
    if (character >= open && character <= close)
        return (0);
    return (-1);
}

int my_isinstr(char c, char *str, int release)
{
    for (int e = 0; str[e]; ++e)
        if (str[e] == c) {
            my_free(str, NULL, NULL, release);
            return (1);
        }
    my_free(str, NULL, NULL, release);
    return (0);
}