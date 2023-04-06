/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** my_str__array_quote
*/

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int check_only_space(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ')
            return (0);
    return (1);
}

char **clean_command(char **tab)
{
    if (!tab || tab[0] == NULL)
        return (NULL);
    tab[0] = strtok(tab[0], " ");
    for (int i = 0; tab[i] != NULL; i++)
        if (check_only_space(tab[i]) == 1)
            for (int i_save = i; tab[i_save] != NULL; i_save++)
                tab[i_save] = tab[i_save + 1];
    return (tab);
}