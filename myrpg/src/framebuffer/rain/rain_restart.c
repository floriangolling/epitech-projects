/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** rain_restart
*/

#include "rpg.h"

void rain_restart(fbf_t *fbf, rain_t *rain)
{
    rain->ic_loop = 0;
    rain->begining = rand() % 5000 + 5000;
    for (int e = 0; e < rain->nb_drop; ++e)
        rain->drop[e].start = (rand() % rain->begining / 2.0) +
        (rand() % rain->begining / 2.0);
    ++fbf->active[RAIN];
    return;
}