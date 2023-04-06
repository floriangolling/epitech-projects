/*
** EPITECH PROJECT, 2020
** framebuffer
** File description:
** framebuffer_pixel
*/

#include "rpg.h"

void put_pixel(bf_t *buffer, int x, int y, sfColor color)
{
    int i = 4 * buffer->size.x * y + x * 4;

    if (IN_BUFFER) {
        buffer->pixels[i] = color.r;
        buffer->pixels[i + 1] = color.g;
        buffer->pixels[i + 2] = color.b;
        buffer->pixels[i + 3] = color.a;
    }
    return;
}

void put_pixel_light(bf_t *buffer, int x, int y, sfColor color)
{
    int i = 4 * buffer->size.x * y + x * 4;

    if (!(IN_BUFFER))
        return;
    if (buffer->pixels[i] < color.r) {
        buffer->pixels[i] = color.r;
        buffer->pixels[i + 1] = color.g;
        buffer->pixels[i + 2] = color.b;
        buffer->pixels[i + 3] = color.a;
        return;
    }
    return;
}