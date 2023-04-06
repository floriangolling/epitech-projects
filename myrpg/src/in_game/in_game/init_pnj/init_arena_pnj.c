/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** init_arena_pnj
*/

#include "rpg.h"

int init_arena_pnj(game_t *game)
{
    if (!(game->game_scenes[ARENA_MAP].pnj = malloc(sizeof(elem_t) * 2)))
        return (1);
    game->game_scenes[ARENA_MAP].pnj[ELF] = create_element(
        game->game_scenes[ARENA_MAP].pnj[ELF],
        "media/enemy/elf/elf_enemy.png", 1000, 0);
    game->game_scenes[ARENA_MAP].pnj[WOMAN] = create_element(
        game->game_scenes[ARENA_MAP].pnj[WOMAN],
        "media/enemy/woman/woman_enemy.png", 800, 600);
    return (0);
}