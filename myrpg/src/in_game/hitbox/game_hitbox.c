/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** game_hitbox
*/

#include "rpg.h"

int init_box(game_t *ga, box_t *obj, sfVector2f pos, char *path)
{
    if (!obj) return (1);
    obj->m = sfImage_createFromFile(path);
    if (!obj->m) return (1);
    obj->pos = pos;
    obj->dim = sfImage_getSize(obj->m);
    obj->box = my_malloc_udb(obj->dim.y, obj->dim.x);
    if (!obj->box) return (1);
    hitbox_read_image(ga, obj);
    return (0);
}

int init_hitbox(game_t *ga)
{
    ga->battle.battle = 0;
    ga->hit.transparent = 0;
    ga->hit.pnj = 0;
    if (init_color(&ga->hit))
        return (1);
    if (init_box(ga, &ga->hit.map, (sfVector2f){0, 0},
    "media/Collisions/outside_collision_remaster.png"))
        return (1);
    return (0);
}

void destroy_hitbox(game_t *ga)
{
    my_free_typoo((void **)ga->hit.map.box);
    my_free_typoo((void **)ga->hit.player.box);
    return;
}