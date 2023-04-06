/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** hitbox_player
*/

#include "rpg.h"

static int pixel_verification(game_t *ga, u_int8_t player, u_int8_t map)
{
    if (RED_MATCH || GREEN_MATCH || GATE_MATCH)
        return (2);
    if (BLUE_MATCH || LOW_BLUE_MATCH)
        ga->hit.transparent = 1;
    for (u_int8_t i = 2; i < ga->hit.ic_c - 1; ++i) {
        if (SCENE_MATCH) {
            ga->fbf.cut.transition = 1;
            ga->fbf.cut.ic_scene = i - 1;
        }
    }
    if (INTERACTION_MATCH)
        ga->hit.pnj = 1;
    return (0);
}

static int hitbox_verification(game_t *ga, elem_t *c, hitbox_t *h)
{
    sfVector2i p;
    bool collision = 0;
    int value = 0;
    p.x = h->player.pos.x;
    p.y = h->player.pos.y;
    h->transparent = 0;
    h->pnj = 0;
    for (int y = 0; y < c->rect.height; ++y) {
        for (int x = 0; x < c->rect.width; ++x) {
            if (OUT_OF_RANGE)
                continue;
            value = pixel_verification(ga, PLAYER_PIXEL, MAP_PIXEL);
            if (value == 1) return (1);
            else if (value == 2)
                collision = 1;
        }
    }
    if (collision)
        return (1);
    return (0);
}

int hitbox_effect(game_t *ga, double n_x, double n_y)
{
    ga->hit.player.pos.x += n_x;
    ga->hit.player.pos.y += n_y;
    if (hitbox_verification(ga, &ga->player.character, &ga->hit)) {
        ga->hit.player.pos.x -= n_x;
        ga->hit.player.pos.y -= n_y;
        return (1);
    }
    return (0);
}