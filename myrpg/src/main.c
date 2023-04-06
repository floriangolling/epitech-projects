/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** main.c
*/

#include "rpg.h"

int (*select_game_state[6])(game_t *game) =
{
    main_menu,
    settings_menu,
    pregame,
    in_game,
    pause_menu,
    end_game
};

int launch_game(game_t *game)
{
    int check_tab = 0;

    while (game->game_state[check_tab] != 1 &&
        game->game_state[check_tab] != 2)
        ++check_tab;
    if (game->game_state[check_tab] == 2) {
        game->game_is_up = false;
        return (0);
    } else
        select_game_state[check_tab](game);
    return (0);
}

int init_game_state_tab(game_t *game)
{
    int init_tab = 0;

    if (!(game->game_state = malloc(sizeof(int) * 7)))
        return (1);
    if (!(game->menu = malloc(sizeof(menu_t) * 6)))
        return (1);
    while (init_tab < 6) {
        game->game_state[init_tab] = 0;
        ++init_tab;
    }
    game->game_state[init_tab] = 2;
    game->game_state[MAIN_MENU] = 1;
    return (0);
}

int init_game(game_t *game)
{
    if (!(game->window = malloc(sizeof(window_t))))
        return (1);
    if (init_game_state_tab(game))
        return (1);
    game->window = create_window(game->window, "my_RPG");
    if (init_framebuffer(game, &game->fbf, 1080, 1920))
        return (1);
    game->game_is_up = true;
    create_music(game);
    game->clock = sfClock_create();
    while (game->game_is_up)
        launch_game(game);
    sfMusic_destroy(game->music);
    framebuffer_destroy(&game->fbf);
    return (0);
}

int main(int ac, char **av)
{
    game_t *game;

    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h') {
        usage();
        return (0);
    }
    if (!(game = malloc(sizeof(game_t))))
        return (84);
    if (init_game(game))
        return (84);
    return (0);
}