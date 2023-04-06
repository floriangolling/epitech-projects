/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** battle_shot
*/

#include "rpg.h"

static void shot_available(game_t *ga, battle_t *ba)
{
    for (int e = 0; e < ba->nb_arrow; ++e)
        if (!ba->arrows[e].send) {
            arrow_send(ga, &ba->arrows[e]);
            break;
        }
}

void battle_shot(game_t *game, battle_t *ba)
{
    if (MOUSE_RELEASED)
        shot_available(game, ba);
    else if (sfMouse_isButtonPressed(sfMouseRight) &&
        game->player.inventory.is_equip_shield == 1) {
        game->player.has_shield = true;
    }
}