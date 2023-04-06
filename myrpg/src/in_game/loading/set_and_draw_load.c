/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** set_and_draw_load
*/

#include "rpg.h"

void draw_loading(game_t *game)
{
    sfRenderWindow_drawText(WINDOW, game->loading.text.string, NULL);
    return;
}

int set_loading_text(game_t *game)
{
    static int i = 1;
    static double time = 0;
    sfTime seconds = sfClock_getElapsedTime(game->loading.clock_load);

    time = time + seconds.microseconds / 1000000.0;
    if (time >= 0.7) {
        sfText_setString(game->loading.text.string,
            game->loading.loading_tab[i]);
        ++i;
        time -= 0.7;
        game->loading.load_time++;
    }
    if (i > 3)
        i = 0;
    return (0);
}