/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** framebuffer_dark
*/

#include "rpg.h"

int init_dark(game_t *ga, dark_t *dark)
{
    dark->nb_halo = 33;
    dark->gradually = 0;
    dark->detected = (sfColor){239, 245, 0, 0};
    dark->halo = malloc(sizeof(halo_t) * (dark->nb_halo + 1));
    if (!dark->halo) return (1);
    for (int e = 0; e < dark->nb_halo; ++e)
        dark->halo[e] = halo_born(&ga->fbf);
    return (0);
}

static void dark_alpha(fbf_t *fbf)
{
    for (int e = 0; e < fbf->dark.nb_halo; ++e) {
        fbf->dark.halo[e].extremity.a = fbf->dark.gradually;
        fbf->dark.halo[e].alpha = fbf->dark.halo[e].extremity.a -
        fbf->dark.halo[e].center.a;
    }
    return;
}

static void dark_restart(fbf_t *fbf)
{
    if (fbf->active[DARK] == 1) {
        dark_random(fbf, &fbf->dark);
        fbf->dark.gradually = 1;
        ++fbf->active[DARK];
    }
    if (fbf->dark.gradually < 230) {
        fbf->dark.gradually += 1;
        dark_alpha(fbf);
    }
    return;
}

int framebuffer_dark(game_t *ga, fbf_t *fbf, dark_t *dark)
{
    dark_restart(fbf);
    if (!ga->fbf.move) return (0);
    for (int e = 1; e < dark->nb_halo; ++e)
        if (HALO_INSIDE)
            put_halo_map(&ga->fbf.buffer, &dark->halo[e], ga->fbf.m);
    halo_position(&dark->halo[0], ga->fbf.p);
    put_halo(&ga->fbf.buffer, &dark->halo[0]);
    return (0);
}

void destroy_dark(dark_t *dark)
{
    free(dark->halo);
    return;
}