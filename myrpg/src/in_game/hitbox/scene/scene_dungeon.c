/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** scene_dungeon
*/

#include "rpg.h"

static void dungeon_player_position(game_t *ga)
{
    ga->hit.player.pos = (sfVector2f){702, 1800};
}

static void scene_enter_dungeon(game_t *ga)
{
    sfSprite_setPosition(ga->game_scenes[DUNGEON_MAP].ui_scene[MAP].sprite,
    (sfVector2f){200, -825});
    dungeon_player_position(ga);
    ga->player.character.set_position = (sfVector2f){904, 975};
    ga->player.pl_not_op.set_position = (sfVector2f){904, 975};
    return;
}

int scene_dungeon(game_t *ga)
{
    if (!ga->game_scenes[CAVE_MAP].dialog_state ||
        ga->player.power < 1800) return (0);
    my_free_typoo((void **)ga->hit.map.box);
    scene_restore(ga);
    cut_wait_before(ga, &ga->fbf.cut, 0);
    if (!ga->player.is_on_scene)
        scene_enter_dungeon(ga);
    else
        exit_scene_arena_woman(ga);
    ga->player.is_on_scene = 4;
    sfSprite_setPosition(ga->player.pl_not_op.sprite,
    ga->player.pl_not_op.set_position);
    sfSprite_setPosition(ga->player.character.sprite,
    ga->player.character.set_position);
    if (init_box(ga, &ga->hit.map, (sfVector2f){0, 0},
    "media/Collisions/dungeon_collision.png")) return (1);
    cut_wait_after(ga, &ga->fbf.cut);
    sfClock_restart(ga->clock);
    return (0);
}