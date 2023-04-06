/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** create character
*/

#include "rpg.h"

int create_character(game_t *game)
{
    select_skin(game);
    select_transparent_skin(game);
    init_character_pos(game);
    game->player.is_on_scene = OUTSIDE_MAP;
    game->player.inventory.inventory_is_open = 0;
    game->player.inventory.has_drop_shield = 0;
    game->player.inventory.has_drop_sword = 1;
    game->player.inventory.is_equip_shield = 0;
    game->player.inventory.is_equip_sword = 0;
    game->player.is_in_fight = 0;
    game->hit.pnj = 0;
    game->player.has_shield = false;
    game->player.is_walking = 0;
    return (0);
}

void init_character_pos(game_t *game)
{
    game->player.character.rect.height = 50;
    game->player.character.rect.left = 0;
    game->player.character.rect.top = 0;
    game->player.character.rect.width = 44;
    sfSprite_setTextureRect(game->player.character.sprite,
        game->player.character.rect);
    game->player.pl_not_op.rect.height = 50;
    game->player.pl_not_op.rect.left = 0;
    game->player.pl_not_op.rect.top = 0;
    game->player.pl_not_op.rect.width = 44;
    sfSprite_setTextureRect(game->player.pl_not_op.sprite,
        game->player.pl_not_op.rect);
    return;
}

void select_skin(game_t *game)
{
    switch (game->player.type) {
        case BLOND_BOY:
            game->player.character = create_element(game->player.character,
                "media/player/walking_blond_boy.png", 820, 480);
            break;
        case BROWN_BOY:
            game->player.character = create_element(game->player.character,
                "media/player/walking_brown_boy.png", 820, 480);
            break;
        case BLOND_GIRL:
            game->player.character = create_element(game->player.character,
                "media/player/walking_blond_girl.png", 820, 480);
            break;
        case BROWN_GIRL:
            game->player.character = create_element(game->player.character,
                "media/player/walking_brown_girl.png", 820, 480);
            break;
    }
    return;
}

void select_transparent_skin(game_t *game)
{
    switch (game->player.type) {
        case BLOND_BOY:
            game->player.pl_not_op = create_element(game->player.pl_not_op,
                "media/player/transparent_walking_blond_boy.png", 820, 480);
            break;
        case BROWN_BOY:
            game->player.pl_not_op = create_element(game->player.pl_not_op,
                "media/player/transparent_walking_brown_boy.png", 820, 480);
            break;
        case BLOND_GIRL:
            game->player.pl_not_op = create_element(game->player.pl_not_op,
                "media/player/transparent_walking_blond_girl.png", 820, 480);
            break;
        case BROWN_GIRL:
            game->player.pl_not_op = create_element(game->player.pl_not_op,
                "media/player/transparent_walking_brown_girl.png", 820, 480);
            break;
    }
    return;
}