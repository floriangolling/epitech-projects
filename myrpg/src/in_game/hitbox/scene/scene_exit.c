/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** exit_scene
*/

#include "rpg.h"

void exit_scene_tavern(game_t *ga)
{
    ga->hit.player.pos = (sfVector2f){196, 210};
    ga->player.character.set_position = (sfVector2f){148, 162};
    ga->player.pl_not_op.set_position = (sfVector2f){148, 162};
    return;
}

void exit_scene_seller(game_t *ga)
{
    ga->hit.player.pos = (sfVector2f){1894, 498};
    ga->player.character.set_position = (sfVector2f){1462, 450};
    ga->player.pl_not_op.set_position = (sfVector2f){1462, 450};
    return;
}

void exit_scene_cave(game_t *ga)
{
    ga->hit.player.pos = (sfVector2f){484, 1848};
    ga->player.character.set_position = (sfVector2f){436, 798};
    ga->player.pl_not_op.set_position = (sfVector2f){436, 798};
    return;
}

void exit_scene_dungeon(game_t *ga)
{
    ga->hit.player.pos = (sfVector2f){2015, 1885};
    ga->player.character.set_position = (sfVector2f){1580.7, 832.7};
    ga->player.pl_not_op.set_position = (sfVector2f){1580.7, 832.7};
    return;
}
