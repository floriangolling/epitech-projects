/*
** EPITECH PROJECT, 2020
** framebuffer
** File description:
** square_shape
*/

#include "rpg.h"

void put_square(bf_t *buffer, square_t sqr)
{
    for (int e = 0; e < sqr.dim.y; e++) {
        for (int j = 0; j < sqr.dim.x; j++) {
            put_pixel(buffer, sqr.pos.x + j, sqr.pos.y + e, sqr.color);
        }
    }
    return;
}