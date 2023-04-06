/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

void ld(info_t *info, char **av)
{
    if (av[1] == NULL || av[2] == NULL || av[2][0] != 'r' || av[3] != NULL)
        exit (84);
    char *regg;
    int dec;
    regg = char_type_first(info, av);
    regg = loop_binary(info, av, regg);
    dec = my_getnbr(regg);
    dec = converter(dec);
    reg(0x02, info);
    reg(dec, info);
    value(av[1], info);
    reg(my_getnbr(av[2]), info);
    return;
}

void live(info_t *infos, char **av)
{
    if (av[1] == NULL || av[1][0] == ' ' || av[1][0] == '\0' || av[2] != NULL)
        exit (84);
    reg(0x01, infos);
    value(av[1], infos);
    return;
}

void last_reg(info_t *info, char **av, int i)
{
    if (av[1 + i][0] != REGISTER && av[2 + i][0] == REGISTER) {
        value(av[1 + i], info);
        reg(my_getnbr(av[2 + i]), info);
    }
    return;
}

void first_reg(info_t *info, char **av, int i)
{
    if (av[1 + i][0] == REGISTER && av[2 + i][0] != REGISTER) {
        reg(my_getnbr(av[1 + i]), info);
        value(av[2 + i], info);
    }
    return;
}