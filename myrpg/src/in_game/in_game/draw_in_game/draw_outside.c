/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** draw file
*/

#include "rpg.h"

void draw_outside(game_t *game)
{
    if (game->game_scenes[TAVERN_MAP].dialog_state == 0)
        drawSprite(WINDOW,
            game->game_scenes[OUTSIDE_MAP].ui_scene[2].sprite, NULL);
    else
        drawSprite(WINDOW,
            game->game_scenes[OUTSIDE_MAP].ui_scene[MAP].sprite, NULL);
    drawSprite(WINDOW,
            game->game_scenes[OUTSIDE_MAP].pnj[PNJ_S].sprite, NULL);
    if (game->game_scenes[OUTSIDE_MAP].dialog_state == 0 &&
        game->game_scenes[TAVERN_MAP].dialog_state == 1)
        drawSprite(WINDOW,
            game->game_scenes[OUTSIDE_MAP].pnj[ENNEMY].sprite, NULL);
    if (game->game_scenes[SELLER_MAP].dialog_state == 1 &&
        game->game_scenes[OUTSIDE_MAP].ui_scene[1].is_display == true)
        drawSprite(WINDOW, game->game_scenes[OUTSIDE_MAP].ui_scene[1].sprite,
            NULL);
    drawSprite(WINDOW, game->trans->sprite, NULL);
    return;
}