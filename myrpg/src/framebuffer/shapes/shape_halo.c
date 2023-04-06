/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** shape_halo
*/

#include "rpg.h"

static v_halo_t init_v_halo(halo_t *circle)
{
    v_halo_t v;

    v.x_circle = 0;
    v.y_circle = 0;
    v.reverse = 0;
    v.save = 0;
    v.i = 360;
    v.c1 = 0;
    v.c2 = 0;
    v.c = circle->center;
    v.safe = v.c;
    return (v);
}

static void put_halo_second(bf_t *buffer, halo_t *circle, v_halo_t *v)
{
    for (int o = v->reverse; o < v->x_circle; ++o) {
        v->c = v->safe;
        v->c2 = 1 - fabs(o / circle->radius);
        v->c.r *= v->c2;
        v->c.g *= v->c2;
        v->c.b *= v->c2;
        v->c.a += circle->alpha * (1 - v->c1 * v->c2);
        put_pixel_light(buffer, o + circle->pos.x,
        v->y_circle  + circle->pos.y, v->c);
    }
}

static void put_halo_map_second(bf_t *buffer, halo_t *circle, v_halo_t *v,
sfVector2f m)
{
    for (int o = v->reverse; o < v->x_circle; ++o) {
        v->c = v->safe;
        v->c2 = 1 - fabs(o / circle->radius);
        v->c.r *= v->c2;
        v->c.g *= v->c2;
        v->c.b *= v->c2;
        v->c.a += circle->alpha * (1 - v->c2 * v->c1);
        put_pixel_light(buffer, o + circle->pos.x + m.x, v->y_circle +
        circle->pos.y + m.y, v->c);
    }
}

void put_halo(bf_t *buffer, halo_t *circle)
{
    v_halo_t v = init_v_halo(circle);

    for (float e = 0; e < 180; e += 0.2, v.i -= 0.2, v.save = v.y_circle) {
        v.c = circle->center;
        v.x_circle = circle->radius * sin(e * CONVERSION);
        v.y_circle = circle->radius * cos(e * CONVERSION);
        v.c1 = 1 - fabs(v.y_circle / circle->radius);
        v.c.r *= v.c1;
        v.c.g *= v.c1;
        v.c.b *= v.c1;
        v.reverse = circle->radius * sin(v.i * CONVERSION);
        if (v.y_circle == v.save) continue;
        v.safe = v.c;
        put_halo_second(buffer, circle, &v);
    }
}

void put_halo_map(bf_t *buffer, halo_t *circle, sfVector2f m)
{
    v_halo_t v = init_v_halo(circle);

    for (float e = 0; e < 180; e += 0.5, v.i -= 0.5, v.save = v.y_circle) {
        v.c = circle->center;
        v.x_circle = circle->radius * sin(e * CONVERSION);
        v.y_circle = circle->radius * cos(e * CONVERSION);
        v.c1 = 1 - fabs(v.y_circle / circle->radius);
        v.c.r *= v.c1;
        v.c.g *= v.c1;
        v.c.b *= v.c1;
        v.reverse = circle->radius * sin(v.i * CONVERSION);
        if (v.y_circle == v.save) continue;
        v.safe = v.c;
        put_halo_map_second(buffer, circle, &v, m);
    }
}