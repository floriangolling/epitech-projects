/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** init inventory
*/

#include "rpg.h"

int init_inventory_object(game_t *game)
{
    game->common.inventory_ui[BIG_SHIELD] = create_element(
        game->common.inventory_ui[BIG_SHIELD],
        "media/inventory/shield_big.png", 1057, 440);
    game->common.inventory_ui[LITTLE_SHIELD] = create_element(
        game->common.inventory_ui[LITTLE_SHIELD],
        "media/inventory/shield_little.png", 924, 549);
    game->common.inventory_ui[BIG_SWORD] = create_element(
        game->common.inventory_ui[BIG_SWORD],
        "media/inventory/bow_big.png", 1060, 575);
    game->common.inventory_ui[LITTLE_SWORD] = create_element(
        game->common.inventory_ui[LITTLE_SWORD],
        "media/inventory/bow_little.png", 576, 547);
    game->common.inventory_ui[SHIELD_SHADOW] = create_element(
        game->common.inventory_ui[SHIELD_SHADOW],
        "media/inventory/shield_shadow.png", 680, 505);
    game->common.inventory_ui[SWORD_SHADOW] = create_element(
        game->common.inventory_ui[SWORD_SHADOW],
        "media/inventory/bow_shadow.png", 785, 467);
    return (0);
}

int create_rectangle_inventory(game_t *game, int num, int x, int y)
{
    game->common.inv_rectangle[num].color = sfTransparent;
    game->common.inv_rectangle[num].rect_size.x = x;
    game->common.inv_rectangle[num].rect_size.y = y;
    game->common.inv_rectangle[num].rect = sfRectangleShape_create();
    sfRectangleShape_setSize(game->common.inv_rectangle[num].rect,
        game->common.inv_rectangle[num].rect_size);
    sfRectangleShape_setFillColor(game->common.inv_rectangle[num].rect,
        game->common.inv_rectangle[num].color);
    sfRectangleShape_setPosition(game->common.inv_rectangle[num].rect,
        game->common.inv_rectangle[num].rect_position);
    game->common.inv_rectangle[num].is_hover = false;
    return (0);
}

int rectangle_set_position(sfRectangleShape *rect, int x, int y)
{
    sfVector2f position;

    position.x = x;
    position.y = y;
    sfRectangleShape_setPosition(rect, position);
    return (0);
}

int init_inventory_rectangle(game_t *game)
{
    if (!(game->common.inv_rectangle = malloc(sizeof(rectangle_t) * 5)))
        return (1);
    create_rectangle_inventory(game, INV_RECT_CLOSE, 51, 51);
    rectangle_set_position(game->common.inv_rectangle[INV_RECT_CLOSE].rect,
        1314, 260);
    create_rectangle_inventory(game, INV_RECT_BSH, 115, 115);
    rectangle_set_position(game->common.inv_rectangle[INV_RECT_BSH].rect,
        1048, 432);
    create_rectangle_inventory(game, INV_RECT_BSW, 115, 115);
    rectangle_set_position(game->common.inv_rectangle[INV_RECT_BSW].rect,
        1048, 570);
    create_rectangle_inventory(game, INV_RECT_LSH, 65, 65);
    rectangle_set_position(game->common.inv_rectangle[INV_RECT_LSH].rect,
        920, 545);
    create_rectangle_inventory(game, INV_RECT_LSW, 65, 65);
    rectangle_set_position(game->common.inv_rectangle[INV_RECT_LSW].rect,
        570, 545);
    return (0);
}

int init_inventory(game_t *game)
{
    if (!(game->common.inventory_ui = malloc(sizeof(elem_t) * 8)))
        return (1);
    game->common.inventory_ui[INV_UI] = create_element(
        game->common.inventory_ui[INV_UI],
        "media/inventory/inventory_ui.png", 544, 248);
    game->common.inventory_ui[INV_CLOSE_HOV] = create_element(
        game->common.inventory_ui[INV_CLOSE_HOV],
        "media/inventory/quit_inventory_hov.png", 1100, 500);
    init_inventory_object(game);
    game->common.close_inv_butt = create_button(game->common.close_inv_butt,
        "media/inventory/quit_inventory_hov.png", 1313, 259);
    init_inventory_rectangle(game);
    if (init_inventory_text(game))
        return (1);
    return (0);
}