/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** my_str
*/

#include "basics.h"

int my_str_isin(char *base, char *in, int release)
{
    int i = 0;
    int e = 0;
    int s_e = 0;

    if (!base || !in) return (0);
    while (base[e]) {
        for (; base[e] && base[e] != in[i]; ++e);
        for (; base[e] && in[i] && base[e] == in[i]; ++e, ++i)
            if (!s_e && i && base[e] == in[0])
                s_e = e;
        if (!in[i]) {
            my_free(base, in, NULL, release);
            return (1);
        } else if (s_e != 0)
            e = s_e;
        s_e = 0;
        i = 0;
    }
    my_free(base, in, NULL, release);
    return (0);
}