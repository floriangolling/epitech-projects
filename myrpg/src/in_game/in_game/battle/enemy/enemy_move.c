/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** enemy_move
*/

#include "rpg.h"

static void move_new_direction(game_t *ga, battle_t *ba, enemy_t *enemy)
{
    if (!enemy->move.x && !enemy->move.y && enemy->arrow.send) {
        enemy->move.x = rand() % 200 - 110;
        enemy->move.y = rand() % 200 - 100;
    } else if (!enemy->move.x && !enemy->move.y && !enemy->arrow.send) {
        arrow_enemy_send(ga, enemy, &enemy->arrow);
        enemy->animate = 1;
    }
    return;
}

void enemy_move(game_t *ga, battle_t *ba, enemy_t *enemy)
{
    if (enemy->move.x < 0) {
        --enemy->pos.x;
        ++enemy->move.x;
    } else if (enemy->move.x > 0) {
        ++enemy->pos.x;
        --enemy->move.x;
    }
    if (enemy->move.y < 0) {
        --enemy->pos.y;
        ++enemy->move.y;
    } else if (enemy->move.y > 0) {
        ++enemy->pos.y;
        --enemy->move.y;
    }
    move_new_direction(ga, ba, enemy);
    return;
}