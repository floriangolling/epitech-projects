/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** enemy_animate
*/

#include "rpg.h"

void enemy_animate(enemy_t *enemy)
{
    if (!enemy->animate) return;
    if (enemy->rect.left <= 0) {
        enemy->rect.left = enemy->saveleft;
        sfSprite_setTextureRect(enemy->sprite, enemy->rect);
        enemy->animate = 0;
        return;
    }
    enemy->rect.left -= enemy->rect.width;
    sfSprite_setTextureRect(enemy->sprite, enemy->rect);
    return;
}