/*
** EPITECH PROJECT, 2020
** framebuffer
** File description:
** framebuffer_restore
*/

#include "rpg.h"

void buffer_restore(bf_t *buffer)
{
    for (int e = 0; e < buffer->size.x * buffer->size.y * 4; e += 4) {
        buffer->pixels[e] = 0;
        buffer->pixels[e + 1] = 0;
        buffer->pixels[e + 2] = 0;
        buffer->pixels[e + 3] = 0;
    }
    return;
}

void buffer_gloomy_restore(bf_t *buffer, sfUint8 alpha)
{
    for (int e = 0; e < buffer->size.x * buffer->size.y * 4; e += 4) {
        buffer->pixels[e] = 0;
        buffer->pixels[e + 1] = 0;
        buffer->pixels[e + 2] = 0;
        buffer->pixels[e + 3] = alpha;
    }
    return;
}