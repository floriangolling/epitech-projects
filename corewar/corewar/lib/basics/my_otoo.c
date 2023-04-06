/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** otoo
*/

#include "basics.h"

static int count_nb_of_part(char *str, char sep_one, char sep_two)
{
    int e = 0;
    int terms = 0;
    int block = 0;

    for (e = 0; str[e] == sep_one || str[e] == sep_two; e++);
    for (; str[e]; e++) {
        if (str[e] != sep_one && str[e] != sep_two && terms == 0) {
            block++;
            terms = 1;
        } else if ((str[e] == sep_one || str[e] == sep_two) && terms == 1) {
            terms = 0;
        }
    }
    return (block);
}

static void space_handling(int *space, char *str, char sep_one, char sep_two)
{
    int e = 0;
    int terms = 0;
    int begin = 0;
    int inc = 0;

    for (; str[e]; e++) {
        if (str[e] != sep_one && str[e] != sep_two && terms == 0) {
            begin = e;
            terms = 1;
        } else if ((str[e] == sep_one || str[e] == sep_two) && terms == 1) {
            space[inc++] = (e - begin) + 1;
            terms = 0;
        }
    }
    if (e != 0 && str[e - 1] != sep_one && str[e - 1] != sep_two)
        space[inc] = (e - begin) + 1;
}

static int init_otoo(otoo_t *s, char *str, char sep_one, char sep_two)
{
    s->i = 0;
    s->e = 0;
    s->o = 0;
    s->nb_part = count_nb_of_part(str, sep_one, sep_two);
    s->space = malloc(sizeof(int) * (s->nb_part + 1));
    s->otoo = malloc(sizeof(char *) * (s->nb_part + 1));

    if (s->space == NULL || s->otoo == NULL)
        return (84);
    return (0);
}

static char **parsing(char *str, char sep_one, char sep_two, int *nb_of_part)
{
    otoo_t s;

    if (init_otoo(&s, str, sep_one, sep_two) != 0) return (NULL);
    space_handling(s.space, str, sep_one, sep_two);
    for (; str[s.o] == sep_one || str[s.o] == sep_two; s.o++);
    for (; s.e < s.nb_part; ++s.e) {
        s.otoo[s.e] = malloc(sizeof(char) * (s.space[s.e] + 1));
        if (s.otoo[s.e] == NULL) return (NULL);
        for (; str[s.o] != sep_one && str[s.o] != sep_two && str[s.o] != '\0';
        ++s.i, ++s.o)
            s.otoo[s.e][s.i] = str[s.o];
        for (;str[s.o] != '\0' &&
        (str[s.o] == sep_one || str[s.o] == sep_two); ++s.o);
        s.otoo[s.e][s.i] = '\0';
        s.i = 0;
    }
    s.otoo[s.e] = NULL;
    free(s.space);
    return (s.otoo);
}

char **my_otoo(char *str, char sep_one, char sep_two, int *nb_of_part)
{
    for (int e = 0; str[e]; e++) {
        if (str[e] == '\t')
            str[e] = sep_one;
    }
    return (parsing(str, sep_one, sep_two, nb_of_part));
}