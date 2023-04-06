/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** enemy_extremity
*/

#include "rpg.h"

void enemy_extremity(game_t *ga, battle_t *ba, enemy_t *enemy)
{
    if (enemy->pos.x > 1798)
        --enemy->pos.x;
    else if (enemy->pos.x < 1000)
        ++enemy->pos.x;
    if (enemy->pos.y < 70)
        ++enemy->pos.y;
    else if (enemy->pos.y > 900)
        --enemy->pos.y;
    sfSprite_setPosition(enemy->sprite, enemy->pos);
    return;
}