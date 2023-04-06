/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** create music
*/

#include "rpg.h"

int create_music(game_t *game)
{
    game->music = sfMusic_createFromFile("media/sounds/music.ogg");
    game->settings.is_music_on = true;
    game->settings.music_volume = 100;
    sfMusic_setVolume(game->music, 50.0);
    sfMusic_setLoop(game->music, true);
    sfMusic_play(game->music);
    return (0);
}