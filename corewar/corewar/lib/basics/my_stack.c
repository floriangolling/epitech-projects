/*
** EPITECH PROJECT, 2020
** lib
** File description:
** my_stack
*/

#include "basics.h"

char **my_push(char **oo, char *o)
{
    int e = 0;
    int i = 0;
    int length = my_oolen(oo);
    char **copy_oo = malloc(sizeof(char *) * (length + 2));

    if (copy_oo == NULL)
        return (NULL);
    for (e = 0; oo[e] != NULL; e++) {
        copy_oo[e] = my_cpy(oo[e], 0);
        if (copy_oo[e] == NULL)
            return (NULL);
    }
    copy_oo[e++] = o;
    copy_oo[e] = NULL;
    my_free_oo(oo);
    return (copy_oo);
}

char **my_pop(char **oo, char *o)
{
    int e = 0;
    int ce = 0;
    int length_oo = my_oolen(oo);
    char *tmp;
    char **copy_oo = malloc(sizeof(char *) * (length_oo + 1));

    if (copy_oo == NULL)
        return (NULL);
    for (; oo[e] != NULL; e++) {
        tmp = my_cpy_lim(oo[e], '=', 0);
        if (my_cmp(tmp, o, 0)) {
            free(tmp);
            continue;
        }
        copy_oo[ce++] = my_cpy(oo[e], 0);
        free(tmp);
    }
    copy_oo[ce] = NULL;
    my_free_oo(oo);
    return (copy_oo);
}