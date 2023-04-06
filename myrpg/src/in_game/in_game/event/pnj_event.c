/*
** EPITECH PROJECT, 2020
** rpg Project
** File description:
** pnj_event
*/

#include "rpg.h"

char *rpg_dialog(game_t *game, char *curr_dialog)
{
    int j = 0;
    int i = game->game_scenes[game->player.is_on_scene].pos_in_dial;

    j = my_strlen(game->game_scenes[game->player.is_on_scene].dialog);
    if (((i - 1) == j) && j != 0)
        return (curr_dialog);
    if (curr_dialog == NULL) {
        if (!(curr_dialog = malloc(sizeof(char) * (j + 2))))
            return (NULL);
    }
    curr_dialog[i] = game->game_scenes[game->player.is_on_scene].dialog[i];
    curr_dialog[i + 1] = '\0';
    ++game->game_scenes[game->player.is_on_scene].pos_in_dial;
    return (curr_dialog);
}

int set_pnj_dialog(game_t *game, char *text)
{
    sfText_setString(game->game_scenes[game->player.is_on_scene].texts.string,
        text);
    return (0);
}

char *clean_str(game_t *game, char *curr)
{
    sfVector2f pos;

    curr[0] = '\0';
    sfText_setString(game->game_scenes[game->player.is_on_scene].texts.string,
        curr);
    free(curr);
    curr = NULL;
    if (game->player.is_on_scene != DUNGEON_MAP)
        choose_pnj_dialog(game);
    if (game->player.is_on_scene == TAVERN_MAP &&
        game->game_scenes[TAVERN_MAP].dialog_state == 2) {
        pos.x = 1231;
        pos.y = 1300;
        sfSprite_setPosition(game->game_scenes[OUTSIDE_MAP].ui_scene[1].sprite,
            pos);
    }
    game->game_scenes[game->player.is_on_scene].dial_activated = false;
    return (curr);
}

int pnj_event(game_t *game)
{
    static double time;
    static char *curr_dialog = NULL;
    game->time = sfClock_getElapsedTime(game->clock);
    time = time + game->time.microseconds / 1000000.0;
    if (game->hit.pnj == 0) {
        time = 0;
        game->game_scenes[game->player.is_on_scene].pos_in_dial = 0;
        if (curr_dialog != NULL)
            curr_dialog = clean_str(game, curr_dialog);
        choose_pnj_dialog(game);
    }
    if (time >= 0.05 && game->hit.pnj == 1 && game->player.is_in_fight == 0) {
        game->game_scenes[game->player.is_on_scene].dial_activated = true;
        curr_dialog = rpg_dialog(game, curr_dialog);
        if (curr_dialog == NULL)
            return (change_state_cause_of_error(game));
        set_pnj_dialog(game, curr_dialog);
        time -= 0.05;
    }
    return (0);
}