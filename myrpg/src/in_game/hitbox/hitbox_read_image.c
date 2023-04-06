/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** hitbox_read_image
*/

#include "rpg.h"

static int color_compare(sfColor o, sfColor t)
{
    if (o.r == t.r && o.g == t.g && o.b == t.b)
        return (1);
    return (0);
}

static int color_compare_two(sfColor o, sfColor t)
{
    if (o.r == t.r && o.g == t.g)
        return (1);
    return (0);
}

static void pixel_read(game_t *ga, box_t *obj, int y, int x)
{
    sfColor c = sfImage_getPixel(obj->m, x, y);
    u_int8_t i = 0;

    obj->box[y][x] = 0;
    if (c.r == 255)
        obj->box[y][x] |= 128;
    if (c.g == 255)
        obj->box[y][x] |= 64;
    if (c.b == 255)
        obj->box[y][x] |= 32;
    for (i = 0; i < ga->hit.ic_c; ++i)
        if (color_compare(c, ga->hit.color[i]))
            obj->box[y][x] = i + 1;
    if (color_compare_two(c, ga->fbf.dark.detected))
        dark_detected(ga, c.b, x, y);
    return;
}

void hitbox_read_image(game_t *ga, box_t *obj)
{
    for (int y = 0; y < obj->dim.y; ++y) {
        for (int x = 0; x < obj->dim.x; ++x) {
            pixel_read(ga, obj, y, x);
        }
    }
    sfImage_destroy(obj->m);
    return;
}