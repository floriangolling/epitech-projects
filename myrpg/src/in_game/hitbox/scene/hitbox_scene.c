/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** hitbox_scene
*/

#include "rpg.h"

void (*exit_scene[])(game_t *ga) = {
    NULL,
    exit_scene_tavern,
    exit_scene_seller,
    exit_scene_cave,
    exit_scene_dungeon,
    exit_scene_arena_elf
};

int scene_outside(game_t *ga)
{
    scene_restore_outside(ga);
    cut_wait_before(ga, &ga->fbf.cut, 1);
    (*exit_scene[ga->player.is_on_scene])(ga);
    ga->player.is_in_fight = 0;
    ga->player.is_on_scene = 0;
    my_free_typoo((void **)ga->hit.map.box);
    sfSprite_setPosition(ga->player.pl_not_op.sprite,
    ga->player.pl_not_op.set_position);
    sfSprite_setPosition(ga->player.character.sprite,
    ga->player.character.set_position);
    if (init_box(ga, &ga->hit.map, (sfVector2f){0, 0},
    "media/Collisions/outside_collision_remaster.png")) return (1);
    cut_wait_after(ga, &ga->fbf.cut);
    sfClock_restart(ga->clock);
    return (0);
}

int scene_tavern(game_t *ga)
{
    my_free_typoo((void **)ga->hit.map.box);
    scene_restore(ga);
    cut_wait_before(ga, &ga->fbf.cut, 0);
    ga->player.is_on_scene = 1;
    ga->hit.player.pos = (sfVector2f){386, 942};
    ga->player.character.set_position = (sfVector2f){883, 944};
    ga->player.pl_not_op.set_position = (sfVector2f){883, 944};
    sfSprite_setPosition(ga->player.pl_not_op.sprite,
    ga->player.pl_not_op.set_position);
    sfSprite_setPosition(ga->player.character.sprite,
    ga->player.character.set_position);
    if (init_box(ga, &ga->hit.map, (sfVector2f){0, 0},
    "media/Collisions/tavern_collision.png")) return (1);
    cut_wait_after(ga, &ga->fbf.cut);
    sfClock_restart(ga->clock);
    return (0);
}

int scene_seller(game_t *ga)
{
    my_free_typoo((void **)ga->hit.map.box);
    scene_restore(ga);
    cut_wait_before(ga, &ga->fbf.cut, 0);
    sfVector2f sh = {847, 1300};
    sfSprite_setPosition(ga->game_scenes[OUTSIDE_MAP].ui_scene[1].sprite, sh);
    ga->player.is_on_scene = 2;
    ga->hit.player.pos = (sfVector2f){386, 930};
    ga->player.character.set_position = (sfVector2f){858, 934};
    ga->player.pl_not_op.set_position = (sfVector2f){858, 934};
    sfSprite_setPosition(ga->player.pl_not_op.sprite,
    ga->player.pl_not_op.set_position);
    sfSprite_setPosition(ga->player.character.sprite,
    ga->player.character.set_position);
    if (init_box(ga, &ga->hit.map, (sfVector2f){0, 0},
    "media/Collisions/seller_collision.png")) return (1);
    cut_wait_after(ga, &ga->fbf.cut);
    sfClock_restart(ga->clock);
    return (0);
}

int scene_cave(game_t *ga)
{
    my_free_typoo((void **)ga->hit.map.box);
    scene_restore(ga);
    cut_wait_before(ga, &ga->fbf.cut, 0);
    sfSprite_setPosition(ga->game_scenes[CAVE_MAP].ui_scene[MAP].sprite,
    (sfVector2f){435, -90});
    sfSprite_setPosition(ga->game_scenes[CAVE_MAP].pnj[PNJ_S].sprite,
    (sfVector2f){1300, 280});
    ga->player.is_on_scene = 3;
    ga->hit.player.pos = (sfVector2f){630, 1048};
    ga->player.character.set_position = (sfVector2f){1065, 958};
    ga->player.pl_not_op.set_position = (sfVector2f){1065, 958};
    sfSprite_setPosition(ga->player.pl_not_op.sprite,
    ga->player.pl_not_op.set_position);
    sfSprite_setPosition(ga->player.character.sprite,
    ga->player.character.set_position);
    if (init_box(ga, &ga->hit.map, (sfVector2f){0, 0},
    "media/Collisions/cave_collision.png")) return (1);
    cut_wait_after(ga, &ga->fbf.cut);
    sfClock_restart(ga->clock);
    return (0);
}