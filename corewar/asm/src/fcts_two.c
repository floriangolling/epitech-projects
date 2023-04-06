/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

void aff(info_t *info, char **av)
{
    if (av[1] == NULL || av[1][0] != REGISTER || av[2] != NULL) {
        exit (84);
    }
    reg(0x10, info);
    char *regg;
    int dec;
    regg = char_type_first(info, av);
    regg = loop_binary(info, av, regg);
    dec = my_getnbr(regg);
    dec = converter(dec);
    reg(dec, info);
    reg(my_getnbr(av[1]), info);
    return;
}

void or(info_t *info, char **av)
{
    if (av[1] == NULL || av[2] == NULL || av[3] == NULL || av[4] != NULL
        || av[3][0] != 'r')
        exit (84);
    reg(0x07, info);
    char *regg;
    int dec;
    regg = char_type_first(info, av);
    regg = loop_binary(info, av, regg);
    dec = my_getnbr(regg);
    dec = converter(dec);
    reg(dec, info);
    double_reg(info, av, 0);
    double_v(info , av, 0);
    first_reg(info, av, 0);
    last_reg(info, av, 0);
    reg(my_getnbr(av[3]), info);
    return;
}

void and(info_t *info, char **av)
{
    if (av[1] == NULL || av[2] == NULL || av[3] == NULL || av[4] != NULL
        || av[3][0] != 'r')
        exit (84);
    reg(0x06, info);
    char *regg;
    int dec;
    regg = char_type_first(info, av);
    regg = loop_binary(info, av, regg);
    dec = my_getnbr(regg);
    dec = converter(dec);
    reg(dec, info);
    double_reg(info, av, 0);
    double_v(info , av, 0);
    first_reg(info, av, 0);
    last_reg(info, av, 0);
    reg(my_getnbr(av[3]), info);
    return;
}

void add(info_t *infos, char **av)
{
    if (av[1] == NULL || av[2] == NULL || av[3] == NULL || av[4] != NULL)
        exit (84);
    reg(0x04, infos);
    reg(converter((my_getnbr("01010100"))), infos);
    reg(my_getnbr(av[1]), infos);
    reg(my_getnbr(av[2]), infos);
    reg(my_getnbr(av[3]), infos);
}

void sub(info_t *infos, char **av)
{
    if (av[1] == NULL || av[2] == NULL || av[3] == NULL || av[4] != NULL)
        exit (84);
    reg(0x05, infos);
    reg(converter((my_getnbr("01010100"))), infos);
    reg(my_getnbr(av[1]), infos);
    reg(my_getnbr(av[2]), infos);
    reg(my_getnbr(av[3]), infos);
}