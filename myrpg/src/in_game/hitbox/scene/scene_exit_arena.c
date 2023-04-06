/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** exit_arena
*/

#include "rpg.h"

void exit_scene_arena_elf(game_t *ga)
{
    sfSprite_setPosition(ga->game_scenes[OUTSIDE_MAP].ui_scene[MAP].sprite,
    (sfVector2f){-435.8, -648.4});
    sfSprite_setPosition(ga->game_scenes[OUTSIDE_MAP].pnj[PNJ_S].sprite,
    (sfVector2f){196, -120});
    sfSprite_setPosition(ga->game_scenes[OUTSIDE_MAP].pnj[ENNEMY].sprite,
    (sfVector2f){1620, 550});
    ga->hit.player.pos = (sfVector2f){2123, 1190};
    ga->player.character.set_position = (sfVector2f){1687.7, 541.6};
    ga->player.pl_not_op.set_position = (sfVector2f){1687.7, 541.6};
    ga->hit.transparent = 1;
    return;
}

void exit_scene_arena_woman(game_t *ga)
{
    if (ga->battle.battle == 2) {
        sfSprite_setPosition(ga->game_scenes[DUNGEON_MAP].ui_scene[MAP].sprite,
        (sfVector2f){200.0, -789.0});
        ga->hit.player.pos = (sfVector2f){438, 1338};
        ga->player.character.set_position = (sfVector2f){640, 549};
        ga->player.pl_not_op.set_position = (sfVector2f){640, 549};
    } else {
        sfSprite_setPosition(ga->game_scenes[DUNGEON_MAP].ui_scene[MAP].sprite,
        (sfVector2f){200.0, -675.0});
        ga->hit.player.pos = (sfVector2f){270, 1218};
        ga->player.character.set_position = (sfVector2f){472, 546};
        ga->player.pl_not_op.set_position = (sfVector2f){472, 546};
    }
    return;
}