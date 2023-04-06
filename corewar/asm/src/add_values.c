/*
** EPITECH PROJECT, 2020
** lib element
** File description:
** check if FD is OK
*/

#include "my.h"
#include "include.h"
#include "struct.h"

int reg(int value, info_t *infos)
{
    if (infos->loop == 0) {
        infos->size += REG;
        return (0);
    }
    write(infos->fd, &value, REG);
    return (0);
}

void swap_bytes(void *value)
{
    unsigned char temp;
    bytes *src = (bytes *)value;
    temp = (*src)[0];
    (*src)[0] = (*src)[1];
    (*src)[1] = temp;
}

void value(char *str, info_t *infos)
{
    int value = 0;
    if (str[0] == DIRECT_CHAR) {
        if (infos->loop == 0) {
            infos->size += 4;
            return;
        }
        value = my_getnbr(str);
        value = BIT_SWAP(value);
        value = (value << 16) | (value >> 16);
        write(infos->fd, &value, 4);
    }
    if (str[0] != DIRECT_CHAR) {
        if (infos->loop == 0) {
            infos->size += 2;
            return;
        }
        value = my_getnbr(str);
        swap_bytes(&value);
        write(infos->fd, &value, 2);
    }
}