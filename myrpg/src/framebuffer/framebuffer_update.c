/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** framebuffer_update
*/

#include "rpg.h"

void framebuffer_update(game_t *ga, fbf_t *fbf, u_int8_t alpha)
{
    sfVector2f m = sfSprite_getPos(ga->game_scenes[MAP].ui_scene[MAP].sprite);
    sfVector2f p = sfSprite_getPos(ga->player.character.sprite);

    fbf->move = 0;
    if (UPDATE_NECESSARY) {
        ga->fbf.m = m;
        ga->fbf.p = p;
        fbf->move = 1;
        buffer_gloomy_restore(&fbf->buffer, alpha);
    }
    return;
}