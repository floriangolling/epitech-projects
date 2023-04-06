/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** dark_born
*/

#include "rpg.h"

halo_t halo_born(fbf_t *fbf)
{
    halo_t halo;

    halo.light_on = 0;
    halo.pos = (sfVector2i){504, 466};
    halo.radius = 100;
    halo.center = (sfColor){255, 147, 41, 180};
    halo.extremity = (sfColor){0, 0, 0, 230};
    halo.alpha = halo.extremity.a - halo.center.a;
    return (halo);
}