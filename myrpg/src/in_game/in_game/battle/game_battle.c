/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** game_battle
*/

#include "rpg.h"

double CONVERSION = 0.017453292519943;
double PI = 3.141592653589;

int init_battle_one(game_t *ga, battle_t *ba)
{
    sfVector2f pos_enemy = {1000, 300};

    ba->end = 0;
    ba->battle = 1;
    ba->nb_arrow = 5;
    ba->nb_enemy = 5;
    ba->hit_player = (sfFloatRect){9, 6, 21, 42};
    ba->hit_enemy = (sfFloatRect){48, 3, 15, 49};
    ba->enemy = malloc(sizeof(enemy_t) * ba->nb_enemy);
    ba->arrows = malloc(sizeof(arrow_t) * ba->nb_arrow);
    if (create_life(ga, &ba->life)) return (1);
    if (!ba->arrows || !ba->enemy) return (1);
    for (int e = 0; e < ba->nb_arrow; ++e)
        if (create_arrow(&ba->arrows[e], "media/battle/arrow_player.png", 300))
            return (1);
    for (int e = 0; e < ba->nb_enemy; ++e) {
        if (create_enemy_elf(&ba->enemy[e], pos_enemy)) return (1);
        pos_enemy.y += 100;
    }
    return (0);
}

int init_battle_two(game_t *ga, battle_t *ba)
{
    sfVector2f pos_enemy = {1000, 300};

    ba->end = 0;
    ba->battle = 2;
    ba->nb_arrow = 5;
    ba->nb_enemy = 7;
    ba->hit_player = (sfFloatRect){9, 6, 21, 42};
    ba->hit_enemy = (sfFloatRect){43, 3, 18, 50};
    ba->enemy = malloc(sizeof(enemy_t) * ba->nb_enemy);
    ba->arrows = malloc(sizeof(arrow_t) * ba->nb_arrow);
    if (create_life(ga, &ba->life)) return (1);
    if (!ba->arrows || !ba->enemy) return (1);
    for (int e = 0; e < ba->nb_arrow; ++e)
        if (create_arrow(&ba->arrows[e], "media/battle/arrow_player.png", 300))
            return (1);
    for (int e = 0; e < ba->nb_enemy; ++e) {
        if (create_enemy_woman(&ba->enemy[e], pos_enemy)) return (1);
        pos_enemy.y += 100;
    }
    return (0);
}

void battle_display(game_t *ga, battle_t *ba)
{
    for (int e = 0; e < ba->nb_arrow; ++e)
        arrow_display(ga, &ba->arrows[e]);
    for (int e = 0; e < ba->nb_enemy; ++e)
        enemy_display(ga, &ba->enemy[e]);
    shield_protect(ga);
    battle_hitbox(ga, ba);
    life_display(ga, &ba->life);
    battle_end(ga, ba);
}

void battle_destroy(battle_t *ba)
{
    for (int e = 0; e < ba->nb_arrow; ++e)
        arrow_destroy(&ba->arrows[e]);
    for (int e = 0; e < ba->nb_enemy; ++e)
        enemy_destroy(&ba->enemy[e]);
    life_destroy(&ba->life);
}