/*
** EPITECH PROJECT, 2020
** PSU_my_ls_2019
** File description:
** my_strcat
*/

#include "basics.h"

char *my_cat(char *one, char *two, int release)
{
    int inc_s = 0;
    char *sum = malloc(sizeof(char) * (my_strlen(one) + my_strlen(two) + 1));

    if (sum == NULL)
        return (NULL);
    for (int e = 0; one[e] != '\0'; e++, inc_s++)
        sum[inc_s] = one[e];
    for (int i = 0; two[i] != '\0'; i++, inc_s++)
        sum[inc_s] = two[i];
    sum[inc_s] = '\0';
    my_free(one, two, NULL, release);
    return (sum);
}

char *nm_cat(char *sum, char *one, char *two, int release)
{
    int inc_s = 0;

    if (!sum || !one || !two) return (NULL);
    for (int e = 0; one[e]; e++, inc_s++)
        sum[inc_s] = one[e];
    for (int i = 0; two[i]; i++, inc_s++)
        sum[inc_s] = two[i];
    sum[inc_s] = '\0';
    my_free(one, two, NULL, release);
    return (sum);
}

char *my_cat_in(char *bread, char *sausage, char ketchup, int release)
{
    int inc_h = 0;
    int inc_b = 0;
    char *hotdog = malloc(my_strlen(bread) + my_strlen(sausage) + 1);

    if (hotdog == NULL)
        return (NULL);
    for (; bread[inc_b] != '\0' && bread[inc_b] != ketchup; inc_b++)
        hotdog[inc_h++] = bread[inc_b];
    hotdog[inc_h++] = bread[inc_b++];
    for (int inc_s = 0; sausage[inc_s] != '\0'; inc_s++)
        hotdog[inc_h++] = sausage[inc_s];
    for (; bread[inc_b] != '\0'; inc_b++)
        hotdog[inc_h++] = bread[inc_b];
    hotdog[inc_h] = '\0';
    my_free(bread, sausage, NULL, release);
    return (hotdog);
}

char *my_catside(char *one, char *two, char *three, int release)
{
    int inc_s = 0;
    char *sum = malloc(my_strlen(one) + my_strlen(two) + my_strlen(three) + 1);

    if (sum == NULL)
        return (NULL);
    for (int e = 0; one[e] != '\0'; e++, inc_s++)
        sum[inc_s] = one[e];
    for (int i = 0; two[i] != '\0'; i++, inc_s++)
        sum[inc_s] = two[i];
    for (int o = 0; three[o] != '\0'; o++, inc_s++)
        sum[inc_s] = three[o];
    sum[inc_s] = '\0';
    my_free(one, two, three, release);
    return (sum);
}