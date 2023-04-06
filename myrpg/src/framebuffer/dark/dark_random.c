/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** dark_random
*/

#include "rpg.h"

void dark_random(fbf_t *fbf, dark_t *dark)
{
    for (int e = 0; e < dark->nb_halo; ++e)
        dark->halo[e].light_on = (rand() % 100) / 40;
    return;
}