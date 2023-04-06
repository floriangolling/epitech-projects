/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** in game
*/

#include "rpg.h"

void *init_in_game(game_t *game)
{
    if (!init_intro(&game->intro)) return ((void *)false);
    init_sprite(&game->intro);
    if (init_in_game_scene(game))
        change_state_cause_of_error(game);
    if (init_hitbox(game))
        change_state_cause_of_error(game);
    if (init_inventory(game))
        change_state_cause_of_error(game);
    init_in_game_text(game);
    return ((void *) 1);
}

int init_in_game_character(game_t *game)
{
    if (create_character(game))
        change_state_cause_of_error(game);
    if (hitbox_select_skin(game))
        change_state_cause_of_error(game);
    return (0);
}

int loop_in_game(game_t *game)
{
    real_morning(game);
    sfRenderWindow_clear(WINDOW, sfBlack);
    if (!game->fbf.cut.is_transition)
        events_in_game(game);
    scene_handling(game, &game->fbf.cut);
    pnj_event(game);
    draw_in_game(game);
    while (game->game_state[PAUSE_MENU] == 1)
        pause_menu(game);
    sfClock_restart(game->clock);
    sfRenderWindow_display(game->window->window);
    return (0);
}

int in_game(game_t *game)
{
    framebuffer_thread(game);
    loading(game);
    init_in_game_character(game);
    sfMusic_pause(game->music);
    intro(game);
    if (game->settings.is_music_on)
        sfMusic_play(game->music);
    sfClock_restart(game->clock);
    while (game->game_state[GAME] == 1)
        loop_in_game(game);
    framebuffer_end(&game->fbf);
    destroy_in_game(game);
    return (0);
}