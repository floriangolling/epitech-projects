/*
** EPITECH PROJECT, 2020
** framebuffer
** File description:
** rain_transition
*/

#include "rpg.h"

static void born_splash(fbf_t *fbf, drop_t *drop)
{
    drop->animation = 1;
    drop->pos.y += drop->dim.y;
    drop->dim.y = 1;
    drop->dim.x = 3;
    drop->color = (sfColor){80, 230, 255, 255};
    return;
}

static void drop_splash_depend_location(game_t *ga, fbf_t *fbf, drop_t *drop)
{
    int y = drop->pos.y + drop->dim.y - (fbf->m.y);
    int x = drop->pos.x -(fbf->m.x);

    if (DROP_CAN_SPLASH) {
        born_splash(fbf, drop);
        return;
    }
    drop_reborn(fbf, drop, rand(), rand());
    return;
}

void drop_transition(game_t *ga, fbf_t *fbf, drop_t *drop)
{
    if (drop->animation) {
        rain_splash(fbf, drop);
        return;
    } else if (drop->pos.y < drop->impact) {
        drop->pos.y += drop->speed;
        return;
    }
    drop_splash_depend_location(ga, fbf, drop);
    return;
}