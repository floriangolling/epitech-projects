/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** event_move
*/

#include "rpg.h"

void is_player_walking(game_t *game)
{
    static int walk = 0;
    static double time = 0;
    sfTime seconds = sfClock_getElapsedTime(game->clock);
    time = time + seconds.microseconds / 1000000.0;
    if (game->player.is_walking == 0) {
        time = 0;
        walk = 1;
    } else {
        if (walk == 1)
            move_rect_player(game);
        while (time >= 0.1) {
            move_rect_player(game);
            time -= 0.1;
        }
        walk = 0;
    }
    return;
}

void change_rect_up(game_t *game)
{
    sfSprite_setTextureRect(game->player.character.sprite,
    game->player.character.rect);
    sfSprite_setTextureRect(game->player.pl_not_op.sprite,
    game->player.character.rect);
    return;
}

void set_open_map(game_t *game)
{
    sfVector2f map = sfSprite_getPos(
        game->game_scenes[OUTSIDE_MAP].ui_scene[MAP].sprite);
    sfSprite_setPosition(game->game_scenes[OUTSIDE_MAP].ui_scene[2].sprite,
        map);
    return;
}

void move_pnj(game_t *game, sfVector2f move)
{
    sfSprite_move(game->game_scenes[OUTSIDE_MAP].ui_scene[MAP].sprite, move);
    sfSprite_move(game->game_scenes[OUTSIDE_MAP].pnj[PNJ_S].sprite, move);
    sfSprite_move(game->game_scenes[OUTSIDE_MAP].pnj[ENNEMY].sprite, move);
    if (game->player.is_on_scene == OUTSIDE_MAP)
        sfSprite_move(game->game_scenes[OUTSIDE_MAP].ui_scene[1].sprite, move);
    set_open_map(game);
    return;
}