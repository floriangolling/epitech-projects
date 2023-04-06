/*
** EPITECH PROJECT, 2020
** PSU_tetris_2019
** File description:
** my_env
*/

#include "basics.h"

char *my_getenv(char *term, char **env)
{
    int len = my_strlen(term);

    for (int e = 0; env[e]; ++e)
        if (my_ncmp(term, env[e], len, 0))
            return ((char *)(env[e] + len));
    return (NULL);
}