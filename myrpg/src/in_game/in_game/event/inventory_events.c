/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** inventory_events
*/

#include "rpg.h"

int is_on_quit_button_ig(game_t *game)
{
    sfFloatRect rect_rect;

    rect_rect = sfRectangleShape_getGlobalBounds(
        game->common.inv_rectangle[INV_RECT_CLOSE].rect);
    game->common.inv_rectangle[INV_RECT_CLOSE].is_hover =
        sfFloatRect_contains(&(rect_rect), MOUSEX, MOUSEY);
    if (game->common.inv_rectangle[INV_RECT_CLOSE].is_hover) {
        game->common.close_inv_butt.is_hover = true;
        return (1);
    } else
        game->common.close_inv_butt.is_hover = false;
    return (0);
}

int inventory_events(game_t *game)
{
    if (game->window->event.type == sfEvtKeyReleased &&
        game->window->event.key.code == sfKeyI) {
        if (game->player.inventory.inventory_is_open == true) {
            game->player.inventory.inventory_is_open = false;
            return (0);
        }
        if (game->player.inventory.inventory_is_open == false)
            game->player.inventory.inventory_is_open = true;
    }
    if (is_on_quit_button_ig(game) && MOUSE_CLICK)
        game->player.inventory.inventory_is_open = false;
    if ((game->player.inventory.has_drop_shield ||
        game->player.inventory.has_drop_sword) && MOUSE_CLICK &&
        game->player.inventory.inventory_is_open)
        equipment(game);
    return (0);
}