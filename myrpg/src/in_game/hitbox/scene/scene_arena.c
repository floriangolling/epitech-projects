/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** scene_battle
*/

#include "rpg.h"

static void arena_player_position(game_t *ga)
{
    ga->hit.player.pos = (sfVector2f){150, 500};
    ga->player.character.set_position = (sfVector2f){150, 500};
    ga->player.pl_not_op.set_position = (sfVector2f){150, 500};
    return;
}

int scene_arena_one(game_t *ga)
{
    if (ga->game_scenes[TAVERN_MAP].dialog_state == 2) return (0);
    if (!ga->player.inventory.is_equip_sword) return (0);
    my_free_typoo((void **)ga->hit.map.box);
    scene_restore(ga);
    cut_wait_before(ga, &ga->fbf.cut, 0);
    sfSprite_setPosition(ga->game_scenes[ARENA_MAP].ui_scene[MAP].sprite,
    (sfVector2f){0, 0});
    ga->player.is_in_fight = 1;ga->player.is_on_scene = 5;
    scene_restore(ga);ga->hit.transparent = 0;
    arena_player_position(ga);
    sfSprite_setPosition(ga->player.pl_not_op.sprite,
    ga->player.pl_not_op.set_position);
    sfSprite_setPosition(ga->player.character.sprite,
    ga->player.character.set_position);
    if (init_battle_one(ga, &ga->battle)) return (1);
    if (init_box(ga, &ga->hit.map, (sfVector2f){0, 0},
    "media/Collisions/arena_collisions.png")) return (1);
    cut_wait_after(ga, &ga->fbf.cut);
    sfClock_restart(ga->clock);
    return (0);
}

int scene_arena_two(game_t *ga)
{
    if (ga->battle.battle == 3) return (0);
    my_free_typoo((void **)ga->hit.map.box);
    scene_restore(ga);
    cut_wait_before(ga, &ga->fbf.cut, 0);
    sfSprite_setPosition(ga->game_scenes[ARENA_MAP].ui_scene[MAP].sprite,
    (sfVector2f){0, 0});
    ga->player.is_in_fight = 1;
    ga->player.is_on_scene = 5;
    ga->hit.transparent = 0;
    arena_player_position(ga);
    sfSprite_setPosition(ga->player.pl_not_op.sprite,
    ga->player.pl_not_op.set_position);
    sfSprite_setPosition(ga->player.character.sprite,
    ga->player.character.set_position);
    if (init_battle_two(ga, &ga->battle)) return (1);
    if (init_box(ga, &ga->hit.map, (sfVector2f){0, 0},
    "media/Collisions/arena_collisions.png")) return (1);
    cut_wait_after(ga, &ga->fbf.cut);
    sfClock_restart(ga->clock);
    return (0);
}