/*
** EPITECH PROJECT, 2019
** putstr
** File description:
** put
*/

#include "basics.h"

int my_putstr(char *str)
{
    return (write(1, str, my_strlen(str)));
}

int nl_putstr(char *str)
{
    write(1, str, my_strlen(str));
    free(str);
}

void my_putrstr(char *str, int release)
{
    write(2, str, my_strlen(str));
    my_free(str, NULL, NULL, release);
}

void my_putcstr(char *str, char *color, int option, int release)
{
    my_putstr("\033[");
    my_putnbr(option);
    my_putstr(color);
    my_putstr(str);
    my_putstr(RESET);
    my_free(str, NULL, NULL, release);
}

void my_putoo(char **oo)
{
    for (int e = 0; oo[e] != NULL; e++) {
        write(1, oo[e], my_strlen(oo[e]));
        write(1, "\n", 1);
    }
}