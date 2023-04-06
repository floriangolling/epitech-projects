/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** game_event
*/

#include "rpg.h"

int shield_animation(game_t *game, int move)
{
    static double time = 0;
    sfTime seconds = sfClock_getElapsedTime(game->clock);
    time = time + seconds.microseconds / 1000000.0;
    int static turn = 0;
    while (time > 0.085) {
        if (turn == 0)
            move++;
        if (move >= 2)
            turn = 1;
        time -= 0.085;
        if (turn == 1)
            move--;
        if (move <= 0)
            turn = 0;
    }
    return (move);
}

void shield_movement(game_t *game, int ic)
{
    int static move = 0;
    sfVector2f pos = sfSprite_getPosition(game->player.character.sprite);
    sfVector2f scale = {0.6, 0.6};
    if (ic == 2 && game->player.has_shield != true &&
        game->player.inventory.is_equip_shield == 1) {
        move = shield_animation(game, move);
        pos.x = pos.x + 10 + move;
        pos.y = pos.y + 18;
        sfSprite_setScale(game->game_scenes[OUTSIDE_MAP].ui_scene[1].sprite,
            scale);
        sfSprite_setPosition(game->game_scenes[OUTSIDE_MAP].ui_scene[1].sprite,
            pos);
    } else if (game->player.has_shield == true &&
        game->player.inventory.is_equip_shield == 1) {
        pos.x = pos.x + 10;
        pos.y = pos.y - 27;
        sfSprite_setPosition(game->game_scenes[OUTSIDE_MAP].ui_scene[1].sprite,
            pos);
    }
    return;
}

void draw_shield_chara(game_t *game)
{
    if ((game->player.character.gen_action == true ||
        game->player.has_shield == true) && game->hit.transparent == false &&
        game->player.inventory.is_equip_shield == 1) {
        drawSprite(game->window->window,
            game->game_scenes[OUTSIDE_MAP].ui_scene[1].sprite, NULL);
    }
    return;
}