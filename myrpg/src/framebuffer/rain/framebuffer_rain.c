/*
** EPITECH PROJECT, 2020
** framebuffer
** File description:
** framebuffer_rain
*/

#include "rpg.h"

int init_rain(game_t *ga, fbf_t *fbf, rain_t *rain)
{
    rain->add = 0;
    rain->mvt = -48;
    rain->begining = 0;
    rain->nb_drop = 3000;
    rain->ic_loop = 0;
    rain->drop = malloc(sizeof(drop_t) * (rain->nb_drop + 1));
    if (!rain->drop) return (1);
    for (int e = 0; e < rain->nb_drop; ++e)
        rain->drop[e] = drop_born(fbf, rand(), rand());
    return (0);
}

static void start_raining(game_t *ga, fbf_t *fbf)
{
    ++fbf->rain.ic_loop;
    for (int e = 0; e < fbf->rain.nb_drop; ++e) {
        if (fbf->rain.drop[e].start < fbf->rain.ic_loop) {
            put_drop(&fbf->buffer, fbf->rain.drop[e]);
            drop_transition(ga, fbf, &fbf->rain.drop[e]);
        }
    }
    return;
}

static void continue_raining(game_t *ga, fbf_t *fbf)
{
    for (int e = 0; e < fbf->rain.nb_drop; ++e) {
        put_drop(&fbf->buffer, fbf->rain.drop[e]);
        drop_transition(ga, fbf, &fbf->rain.drop[e]);
    }
    return;
}

int framebuffer_rain(game_t *ga, fbf_t *fbf)
{
    if (fbf->active[RAIN] == 1)
        rain_restart(fbf, &fbf->rain);
    if (fbf->rain.ic_loop < fbf->rain.begining)
        start_raining(ga, fbf);
    else
        continue_raining(ga, fbf);
    return (0);
}

void destroy_rain(rain_t *rain)
{
    free(rain->drop);
    return;
}