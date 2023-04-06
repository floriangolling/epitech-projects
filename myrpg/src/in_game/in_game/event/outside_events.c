/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** game_event
*/

#include "rpg.h"

int drop_shield(game_t *game)
{
    sfVector2f pos_player;
    sfVector2f pos_map;
    static bool check_pos = false;

    pos_map = sfSprite_getPosition(
        game->game_scenes[OUTSIDE_MAP].ui_scene[BACK].sprite);
    pos_player = sfSprite_getPosition(game->player.character.sprite);
    if (check_pos == true && pos_map.y > -600)
        check_pos = false;
    if (pos_map.y < -700)
        check_pos = true;
    if (pos_player.x >= 945 && pos_player.x <= 975 && pos_map.y > -796 &&
        check_pos && pos_map.x >= -328 && pos_map.x <= -305) {
        game->game_scenes[OUTSIDE_MAP].ui_scene[1].is_display = false;
        game->player.inventory.has_drop_shield = true;
        game->game_scenes[SELLER_MAP].dialog_state = 2;
    }
    return (0);
}

int outside_events(game_t *game)
{
    if (game->game_scenes[OUTSIDE_MAP].dialog_state == 1)
        return (0);
    if (game->game_scenes[OUTSIDE_MAP].dialog_state == 2) {
        game->game_scenes[OUTSIDE_MAP].dialog =
            read_file("media/pnj/outside_dialog_next");
    } else if (game->game_scenes[OUTSIDE_MAP].dialog_state == 0) {
        game->game_scenes[OUTSIDE_MAP].dialog =
            read_file("media/pnj/idle_dialog");
    }
    if (game->game_scenes[OUTSIDE_MAP].dialog == NULL)
        return (1);
    if (game->game_scenes[OUTSIDE_MAP].ui_scene[1].is_display == true)
        drop_shield(game);
    return (0);
}