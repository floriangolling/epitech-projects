/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** game_battle
*/

#include "rpg.h"

void shield_protect(game_t *game)
{
    static bool has_shielded = false;
    static double time = 0;
    sfTime seconds = sfClock_getElapsedTime(game->clock);
    time = time + seconds.microseconds / 1000000.0;
    if (game->player.has_shield == true && has_shielded == false) {
        if (time > 3) {
            time = 0;
            game->player.has_shield = false;
            has_shielded = true;
        }
    }
    if (has_shielded == true) {
        game->player.has_shield = false;
        if (time > 5) {
            has_shielded = false;
            time = 0;
        }
    } else
        time = 0;
    return;
}