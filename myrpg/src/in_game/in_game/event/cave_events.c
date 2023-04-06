/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** game_event
*/

#include "rpg.h"

int cave_events(game_t *game)
{
    if (game->game_scenes[CAVE_MAP].dialog_state == 1) {
        game->game_scenes[CAVE_MAP].dialog =
            read_file("media/pnj/cave_dialog");
    } else if (game->game_scenes[CAVE_MAP].dialog_state == 2) {
        game->game_scenes[CAVE_MAP].dialog =
            read_file("media/pnj/cave_dialog_go_to");
    } else {
        game->game_scenes[CAVE_MAP].dialog =
            read_file("media/pnj/idle_dialog_cave");
    }
    if (game->game_scenes[CAVE_MAP].dialog == NULL)
        return (1);
    return (0);
}

void move_down_cave(game_t *ga, float time)
{
    sfVector2f map = sfSprite_getPos(
        ga->game_scenes[CAVE_MAP].ui_scene[MAP].sprite);
    sfVector2f player = sfSprite_getPos(ga->player.character.sprite);
    sfVector2f move = {0, -400 * time};

    ga->player.character.rect.top = -1;
    change_rect_up(ga);
    if (map.y > -120 && player.y > 540) {
        if (hitbox_effect(ga, 0, 400 * time))
            return;
        sfSprite_move(ga->game_scenes[CAVE_MAP].ui_scene[MAP].sprite, move);
        sfSprite_move(ga->game_scenes[CAVE_MAP].pnj[PNJ_S].sprite, move);
    } else
        move_character(ga, 0, 400 * time);
    return;
}

void move_up_cave(game_t *ga, float time)
{
    sfVector2f map = sfSprite_getPos(
        ga->game_scenes[CAVE_MAP].ui_scene[MAP].sprite);
    sfVector2f player = sfSprite_getPos(ga->player.character.sprite);
    sfVector2f move = {0, 400 * time};

    ga->player.character.rect.top = 147;
    change_rect_up(ga);
    if (map.y < -50 && player.y < 540) {
        if (hitbox_effect(ga, 0, -400 * time))
            return;
        sfSprite_move(ga->game_scenes[CAVE_MAP].ui_scene[MAP].sprite, move);
        sfSprite_move(ga->game_scenes[CAVE_MAP].pnj[PNJ_S].sprite, move);
    } else
        move_character(ga, 0, -400 * time);
    return;
}