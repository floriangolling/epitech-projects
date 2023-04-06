/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** enemy_dodge
*/

#include "rpg.h"

static void dodge_left_or_right(battle_t *ba, enemy_t *enemy, sfVector2f point,
    sfVector2f middle)
{
    float y_center = enemy->pos.y + 26;
    float dif = point.y - middle.y;

    enemy->move.x = 50;
    enemy->move.y = 0;
    if (point.y < y_center && dif < 0) {
        ++enemy->pos.y;
        return;
    } else if (point.y > y_center && dif > 0) {
        --enemy->pos.y;
        return;
    }
    if (dif < 0)
        enemy->pos.y += 2;
    else if (dif > 0)
        enemy->pos.y -= 2;
    return;
}

void enemy_dodge(game_t *ga, battle_t *ba, enemy_t *enemy)
{
    sfFloatRect check;
    sfVector2f point;

    check.left = enemy->pos.x - 60;
    check.top = enemy->pos.y - 60;
    check.width = 100;
    check.height = 170;
    for (int e = 0; e < ba->nb_arrow; ++e) {
        point.x = ba->arrows[e].pos.x + ba->arrows[e].tip.x;
        point.y = ba->arrows[e].pos.y + ba->arrows[e].tip.y;
        if (sfFloatRect_contains(&check, point.x, point.y)) {
            dodge_left_or_right(ba, enemy, point, ba->arrows[e].pos);
            break;
        }
    }
    return;
}