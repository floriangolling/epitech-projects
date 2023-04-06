/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** battle_life
*/

#include "rpg.h"

int create_life(game_t *ga, life_t *life)
{
    life->nb_life = 10;
    life->color = (sfColor){0, 255, 0, 255};
    life->size = (sfVector2f){400, 40};
    life->health = sfRectangleShape_create();
    life->back = sfRectangleShape_create();
    if (!life->health || !life->back) return (1);
    sfRectangleShape_setFillColor(life->health, life->color);
    sfRectangleShape_setSize(life->health, life->size);
    sfRectangleShape_setPosition(life->health, (sfVector2f){50, 24});
    sfRectangleShape_setFillColor(life->back, sfBlack);
    sfRectangleShape_setSize(life->back,
    (sfVector2f){life->size.x + 8, life->size.y + 8});
    sfRectangleShape_setPosition(life->back, (sfVector2f){46, 20});
    return (0);
}

void life_decrease(game_t *ga, life_t *life)
{
    if (ga->player.has_shield == true &&
                                    ga->player.inventory.is_equip_shield == 1)
        return;
    --life->nb_life;
    life->color.r = ((10 - life->nb_life) / 10.0) * 255;
    life->color.g = (life->nb_life / 10.0) * 255;
    life->size.x = (400 / 10.0) * life->nb_life;
    sfRectangleShape_setFillColor(life->health, life->color);
    sfRectangleShape_setSize(life->health, life->size);
    return;
}

void life_display(game_t *ga, life_t *life)
{
    sfRenderWindow_drawRectangleShape(ga->window->window, life->back, NULL);
    sfRenderWindow_drawRectangleShape(ga->window->window, life->health, NULL);
}

void life_destroy(life_t *life)
{
    sfRectangleShape_destroy(life->health);
    sfRectangleShape_destroy(life->back);
}