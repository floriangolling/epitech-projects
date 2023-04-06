/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** draw pregame
*/

#include "rpg.h"

void draw_smiling_face(game_t *game)
{
    for (int i = 0; i < 4; ++i) {
        if (game->menu[PREGAME].buttons[i].is_hover) {
            drawSprite(WINDOW, game->menu[PREGAME].buttons[i + 4].sprite, NULL);
            if (MOUSE_CLICK) {
                game->player.type = i;
                game->game_state[PREGAME] = 0;
                game->game_state[GAME] = 1;
            }
        }
    }
    return;
}

void draw_pregame(game_t *game)
{
    drawSprite(WINDOW, game->menu[PREGAME].ui_scene[BACK].sprite, NULL);
    drawSprite(WINDOW, game->menu[PREGAME].ui_scene[PREGAME_UI].sprite, NULL);
    drawSprite(WINDOW, game->menu[PREGAME].buttons[BLOND_BOY].sprite, NULL);
    drawSprite(WINDOW, game->menu[PREGAME].buttons[BROWN_BOY].sprite, NULL);
    drawSprite(WINDOW, game->menu[PREGAME].buttons[BLOND_GIRL].sprite, NULL);
    drawSprite(WINDOW, game->menu[PREGAME].buttons[BROWN_GIRL].sprite, NULL);
    draw_smiling_face(game);
    return;
}