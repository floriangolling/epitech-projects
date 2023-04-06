/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_strcmp
*/

#include "basics.h"

int my_strcmp(char *s1, char *s2, int release)
{
    int e = 0;

    for (; s1[e] != '\0' || s2[e] != '\0'; e++) {
        if (s1[e] < s2[e]) {
            my_free(s1, s2, NULL, release);
            return (-1);
        } else if (s1[e] > s2[e]) {
            my_free(s1, s2, NULL, release);
            return (1);
        }
    }
    my_free(s1, s2, NULL, release);
    return (0);
}

int my_cmp(char *s1, char *s2, int release)
{
    int e = 0;

    for (; s1[e] != '\0' || s2[e] != '\0'; e++) {
        if (s1[e] < s2[e] || s1[e] > s2[e]) {
            my_free(s1, s2, NULL, release);
            return (0);
        }
    }
    my_free(s1, s2, NULL, release);
    return (1);
}

int my_ncmp(char *s1, char *s2, int n, int release)
{
    int e = 0;

    for (; (s1[e] || s2[e]) && e < n; e++) {
        if (s1[e] != s2[e]) {
            my_free(s1, s2, NULL, release);
            return (0);
        }
    }
    my_free(s1, s2, NULL, release);
    return (1);
}

static void free_two(char *str_one, char *str_two)
{
    free(str_one);
    free(str_two);
}

int my_strcmp_low(char *s1, char *s2, int release)
{
    int e = 0;
    char *tmp_s1 = my_cpy(s1, 0);
    char *tmp_s2 = my_cpy(s2, 0);

    my_lowcase(tmp_s1);
    my_lowcase(tmp_s2);
    for (e = 0; tmp_s1[e] != '\0' || tmp_s2[e] != '\0'; e++) {
        if (tmp_s1[e] < tmp_s2[e]) {
            free_two(tmp_s1, tmp_s2);
            my_free(s1, s2, NULL, release);
            return (-1);
        } else if (tmp_s1[e] > tmp_s2[e]) {
            free_two(tmp_s1, tmp_s2);
            my_free(s1, s2, NULL, release);
            return (1);
        }
    }
    free_two(tmp_s1, tmp_s2);
    my_free(s1, s2, NULL, release);
    return (0);
}