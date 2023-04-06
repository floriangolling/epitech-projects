/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

void double_reg(info_t *info, char **av, int i)
{
    if (av[1 + i][0] == REGISTER && av[2 + i][0] == REGISTER) {
        reg(my_getnbr(av[1 + i]), info);
        reg(my_getnbr(av[2 + i]), info);
    }
    return;
}

void double_v(info_t *info, char **av, int i)
{
    if (av[1 + i][0] != REGISTER && av[2 + i][0] != REGISTER) {
        value(av[1 + i], info);
        value(av[2 + i], info);
    }
    return;
}

void lld(info_t *info, char **av)
{
    if (av[1] == NULL || av[2] == NULL || av[2][0] != 'r' || av[3] != NULL)
        exit (84);
    char *regg;
    int dec;
    regg = char_type_first(info, av);
    regg = loop_binary(info, av, regg);
    dec = my_getnbr(regg);
    dec = converter(dec);
    reg(0x0d, info);
    reg(dec, info);
    value(av[1], info);
    reg(my_getnbr(av[2]), info);
    return;
}

void sti(info_t *info, char **av)
{
    if (av[1] == NULL  || av[2] == NULL || av[3] != NULL ||
        av[1][0] != REGISTER) {
        exit (84);
    }
    reg(0x0b, info);
    char *regg;
    int dec;
    regg = char_type_first(info, av);
    regg = loop_binary(info, av, regg);
    dec = my_getnbr(regg);
    dec = converter(dec);
    reg(dec, info);
    reg(my_getnbr(av[1]), info);
    double_reg(info, av, 1);
    double_v(info , av, 1);
    first_reg(info, av, 1);
    last_reg(info, av, 1);
    return;
}

void xor(info_t *info, char **av)
{
    if (av[1] == NULL || av[2] == NULL || av[3] == NULL || av[4] != NULL
    || av[3][0] != 'r')
        exit (84);
    reg(0x08, info);
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