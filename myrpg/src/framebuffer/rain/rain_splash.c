/*
** EPITECH PROJECT, 2020
** framebuffer
** File description:
** rain_splash
*/

#include "rpg.h"

static void put_splash(fbf_t *fbf, drop_t *drop)
{
    int x_circle = 0;
    int y_circle = 0;

    for (double e = 0; e < 360; e += 25) {
        x_circle = drop->dim.x * cos(e * CONVERSION) + drop->pos.x;
        y_circle = drop->dim.y * sin(e * CONVERSION) + drop->pos.y;
        put_pixel(&fbf->buffer, x_circle, y_circle, drop->color);
    }
    return;
}

static void move_splash(fbf_t *fbf, drop_t *drop)
{
    drop->dim.x += 3;
    ++drop->dim.y;
    if (drop->dim.x < drop->impact / 100)
        drop->pos.y -= 6;
    else if (drop->dim.x < drop->impact / 50)
        drop->pos.y += 3;
    else
        drop_reborn(fbf, drop, rand(), rand());
    return;
}

void rain_splash(fbf_t *fbf, drop_t *drop)
{
    put_splash(fbf, drop);
    move_splash(fbf, drop);
    return;
}