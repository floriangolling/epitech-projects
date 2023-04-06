/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** intro
*/

#include "rpg.h"

static bool extend(intro_t *intro, int *limit)
{
    if (intro->inc.x == limit[intro->inc.y]) {
        if (intro->inc.y++ == 7) return (false);
        sfSprite_setTexture(intro->tilesheet, intro->texture[intro->inc.y],
        false);
        intro->rect = (sfIntRect){0, 0, 960, 540};
        intro->inc.x = 1;
    } else if (!(intro->inc.x % 10)) {
        intro->rect.top += 540;
        intro->rect.left = 0;
    } else intro->rect.left += 960;
    return (true);
}

static bool update(intro_t *intro, game_t *game, int *limit)
{
    if (intro->seconds >= .084) {
        if (!(extend(intro, limit))) return (false);
        intro->inc.x++;
        sfSprite_setTextureRect(intro->tilesheet, intro->rect);
        sfClock_restart(game->clock);
    }
    return (true);
}

int events_intro(game_t *game)
{
    while (sfRenderWindow_pollEvent(game->window->window,
        &(game->window->event))) {
        if (game->window->event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window->window);
            game->game_state[GAME] = 0;
            game->game_is_up = 0;
            return (1);
        }
        if (game->window->event.type == sfEvtKeyReleased &&
            game->window->event.key.code == sfKeyEscape)
            return (1);
    }
    return (0);
}

bool intro(game_t *game)
{
    sfMusic *music = sfMusic_createFromFile("media/intro/sound.ogg");
    int limit[8] = {150, 99, 100, 138, 87, 133, 120, 27};

    sfMusic_play(music);
    while (true) {
        game->intro.time = sfClock_getElapsedTime(game->clock);
        game->intro.seconds = game->intro.time.microseconds / 1000000.0;
        if (!(update(&game->intro, game, limit))) break;
        if (events_intro(game))
            break;
        sfRenderWindow_drawSprite(WINDOW, game->intro.tilesheet, NULL);
        sfRenderWindow_display(WINDOW);
    }
    sfMusic_destroy(music);
    return (true);
}