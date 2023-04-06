/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

int pwr(int nb, int i)
{
    int result = 1;

    if (i == 0)
        return (result);
    for (; i >= 1; i--) {
        result *= nb;
    }
    return (result);
}

int converter(int binary)
{
    int dec = 0;
    int i = 0;
    int rest = 0;

    while (binary != 0) {
        rest = binary % 10;
        binary /= 10;
        dec += rest * pwr(2, i);
        i++;
    }
    return (dec);
}

char *loop_binary(info_t *info, char **av, char *result)
{
    for (int i = 2; av[i]; i++) {
        if (av[i][0] == DIRECT_CHAR)
            result = concat(result, "10");
        else if (av[i][0] == REGISTER)
            result = concat(result, "01");
        else
            result = concat(result, "11");
    }
    while (my_strlen(result) < 8) {
        result = concat(result, "0");
    }
    return (result);
}

char *char_type_first(info_t *info, char **av)
{
    char *result;

    if (av[1][0] == DIRECT_CHAR)
        result = "10";
    else if (av[1][0] == REGISTER)
        result = "01";
    else
        result = "11";
    return (result);
}

void st(info_t *info, char **av)
{
    if (av[1] == NULL  || av[2] == NULL || av[3] != NULL ||
                                                        av[1][0] != REGISTER) {
        exit (84);
    }
    reg(0x03, info);
    char *regg;
    int dec;
    regg = char_type_first(info, av);
    regg = loop_binary(info, av, regg);
    dec = my_getnbr(regg);
    dec = converter(dec);
    reg(dec, info);
    reg(my_getnbr(av[1]), info);
    value(av[2], info);
    return;
}