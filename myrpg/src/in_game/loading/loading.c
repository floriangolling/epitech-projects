/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** loading
*/

#include "rpg.h"

int init_loading(game_t *game)
{
    if (init_text_loading(game))
        return (1);
    game->loading.clock_load = sfClock_create();
    game->loading.load_time = 0;
    sfText_setString(game->loading.text.string, game->loading.loading_tab[0]);
    return (0);
}

void loading(game_t *game)
{
    sfThread *thread;
    bool run_thread = true;
    void *ptr = &init_in_game;
    thread = sfThread_create(ptr, game);
    if (init_loading(game))
        change_state_cause_of_error(game);
    sfClock_restart(game->loading.clock_load);
    while (game->loading.load_time < 8) {
        sfRenderWindow_clear(WINDOW, sfBlack);
        set_loading_text(game);
        draw_loading(game);
        if (run_thread == true) {
            sfThread_launch(thread);
            run_thread = false;
        }
        sfClock_restart(game->loading.clock_load);
        sfRenderWindow_display(game->window->window);
    }
    sfThread_destroy(thread);
    destroy_loading(game);
}

void destroy_loading(game_t *game)
{
    sfText_destroy(game->loading.text.string);
    sfFont_destroy(game->loading.text.font);
    sfClock_destroy(game->loading.clock_load);
    return;
}