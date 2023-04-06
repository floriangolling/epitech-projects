/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** game_event
*/

#include "rpg.h"

int dungeon_events(game_t *game)
{
    game->player.character.get_position =
        sfSprite_getPosition(game->player.character.sprite);
    if (game->player.character.get_position.y <= 170) {
        game->game_state[GAME] = 0;
        game->game_state[END_GAME] = 1;
    }
    return (0);
}

void move_down_dungeon(game_t *ga, float time)
{
    sfVector2f map = sfSprite_getPos(
        ga->game_scenes[DUNGEON_MAP].ui_scene[MAP].sprite);
    sfVector2f player = sfSprite_getPos(ga->player.character.sprite);
    sfVector2f move = {0, -400 * time};

    ga->player.character.rect.top = -1;
    change_rect_up(ga);
    if (map.y > -849 && player.y > 540) {
        if (hitbox_effect(ga, 0, 400 * time))
            return;
        sfSprite_move(ga->game_scenes[DUNGEON_MAP].ui_scene[MAP].sprite, move);
    } else
        move_character(ga, 0, 400 * time);
    return;
}

void move_up_dungeon(game_t *ga, float time)
{
    sfVector2f map = sfSprite_getPos(
        ga->game_scenes[DUNGEON_MAP].ui_scene[MAP].sprite);
    sfVector2f player = sfSprite_getPos(ga->player.character.sprite);
    sfVector2f move = {0, 400 * time};

    ga->player.character.rect.top = 147;
    change_rect_up(ga);
    if (map.y < -53 && player.y < 540) {
        if (hitbox_effect(ga, 0, -400 * time))
            return;
        sfSprite_move(ga->game_scenes[DUNGEON_MAP].ui_scene[MAP].sprite, move);
    } else
        move_character(ga, 0, -400 * time);
    return;
}