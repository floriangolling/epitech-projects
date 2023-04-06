/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** event_move
*/

#include "rpg.h"

void move_character(game_t *game, float x, float y)
{
    sfVector2f offset = {x, y};

    if (hitbox_effect(game, x, y))
        return;
    sfSprite_move(game->player.character.sprite, offset);
    sfSprite_move(game->player.pl_not_op.sprite, offset);
    return;
}

void move_left(game_t *ga, double time)
{
    sfVector2f map = sfSprite_getPos(
        ga->game_scenes[OUTSIDE_MAP].ui_scene[MAP].sprite);
    sfVector2f player = sfSprite_getPos(ga->player.character.sprite);
    sfVector2f move = {400 * time, 0};
    ga->player.character.gen_action = false;
    ga->player.character.rect.top = 48;
    change_rect_up(ga);
    if (ga->player.is_on_scene != OUTSIDE_MAP)
        return (move_character(ga, -400 * time, 0));
    if (map.x < -50 && player.x < 960) {
        if (hitbox_effect(ga, -400 * time, 0))
            return;
        move_pnj(ga, move);
    } else
        move_character(ga, -400 * time, 0);
    return;
}

void move_right(game_t *ga, double time)
{
    sfVector2f map = sfSprite_getPos(
        ga->game_scenes[OUTSIDE_MAP].ui_scene[MAP].sprite);
    sfVector2f player = sfSprite_getPos(ga->player.character.sprite);
    sfVector2f move = {-400 * time, 0};
    ga->player.character.gen_action = false;
    ga->player.character.rect.top = 96;
    change_rect_up(ga);
    if (ga->player.is_on_scene != OUTSIDE_MAP)
        return (move_character(ga, 400 * time, 0));
    if (map.x > -430 && player.x > 960) {
        if (hitbox_effect(ga, 400 * time, 0))
            return;
        move_pnj(ga, move);
    } else
        move_character(ga, 400 * time, 0);
    return;
}

void move_up(game_t *ga, double time)
{
    sfVector2f map = sfSprite_getPos(
        ga->game_scenes[OUTSIDE_MAP].ui_scene[MAP].sprite);
    sfVector2f player = sfSprite_getPos(ga->player.character.sprite);
    sfVector2f move = {0, 400 * time};
    ga->player.character.gen_action = true;
    if (ga->player.is_on_scene == DUNGEON_MAP)
        return (move_up_dungeon(ga, time));
    else if (ga->player.is_on_scene == CAVE_MAP)
        return (move_up_cave(ga, time));
    ga->player.character.rect.top = 147;
    change_rect_up(ga);
    if (ga->player.is_on_scene != OUTSIDE_MAP)
        return (move_character(ga, 0, -400 * time));
    if (map.y < -50 && player.y < 540) {
        if (hitbox_effect(ga, 0, -400 * time))
            return;
        move_pnj(ga, move);
    } else
        move_character(ga, 0, -400 * time);
    return;
}

void move_down(game_t *ga, double time)
{
    ga->player.character.gen_action = false;
    if (ga->player.is_on_scene == DUNGEON_MAP)
        return (move_down_dungeon(ga, time));
    else if (ga->player.is_on_scene == CAVE_MAP)
        return (move_down_cave(ga, time));
    sfVector2f map = sfSprite_getPos(
                        ga->game_scenes[OUTSIDE_MAP].ui_scene[MAP].sprite);
    sfVector2f player = sfSprite_getPos(ga->player.character.sprite);
    sfVector2f move = {0, -400 * time};
    ga->player.character.rect.top = -1;
    change_rect_up(ga);
    if (ga->player.is_on_scene != OUTSIDE_MAP)
        return (move_character(ga, 0, 400 * time));
    if (map.y > -1050 && player.y > 540) {
        if (hitbox_effect(ga, 0, 400 * time))
            return;
        move_pnj(ga, move);
    } else
        move_character(ga, 0, 400 * time);
    return;
}