/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** battle_hitbox
*/

#include "rpg.h"

static void battle_hitplayer(game_t *ga, battle_t *ba)
{
    sfVector2f p = sfSprite_getPosition(ga->player.character.sprite);
    sfFloatRect player = ba->hit_player;

    player.left += p.x;
    player.top += p.y;
    for (int e = 0; e < ba->nb_enemy; ++e) {
        if (PLAYER_IS_HIT) {
            life_decrease(ga, &ba->life);
            ba->enemy[e].arrow.send = 0;
        }
    }
}

static void battle_hitenemy(game_t *ga, battle_t *ba)
{
    sfFloatRect enemy = ba->hit_enemy;

    for (int i = 0; i < ba->nb_enemy; ++i) {
        enemy.left += ba->enemy[i].pos.x;
        enemy.top += ba->enemy[i].pos.y;
        for (int e = 0; e < ba->nb_arrow; ++e) {
            if (ENEMY_IS_HIT)
                ba->enemy[i].alive = 0;
        }
        enemy = ba->hit_enemy;
    }
}

static void bounce_effect(enemy_t *one, enemy_t *two)
{
    if ((one->pos.y > two->pos.y && one->move.y <= 0 && two->move.y >= 0)
        || (one->pos.y < two->pos.y && one->move.y >= 0 && two->move.y <= 0)) {
        one->move.y *= -1;
        two->move.y *= -1;
    }
    if ((one->pos.x > two->pos.x && one->move.x <= 0 && two->move.x >= 0)
        || (one->pos.x < two->pos.x && one->move.x >= 0 && two->move.x <= 0)) {
        one->move.x *= -1;
        two->move.x *= -1;
    }
}

static void battle_bounce(game_t *ga, battle_t *ba)
{
    sfFloatRect enemy1 = ba->hit_enemy;
    sfFloatRect enemy2 = ba->hit_enemy;

    for (int e = 0; e < ba->nb_enemy; ++e) {
        enemy1.left += ba->enemy[e].pos.x;
        enemy1.top += ba->enemy[e].pos.y;
        for (int i = e + 1; i < ba->nb_enemy; ++i) {
            enemy2.left += ba->enemy[i].pos.x;
            enemy2.top += ba->enemy[i].pos.y;
            if (ENEMY_BOUNCE)
                bounce_effect(&ba->enemy[e], &ba->enemy[i]);
            enemy2 = ba->hit_enemy;
        }
        enemy1 = ba->hit_enemy;
    }
    return;
}

void battle_hitbox(game_t *ga, battle_t *ba)
{
    battle_hitenemy(ga, ba);
    battle_hitplayer(ga, ba);
    battle_bounce(ga, ba);
    return;
}