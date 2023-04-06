/*
** EPITECH PROJECT, 2021
** user
** File description:
** users
*/

#include "../include/prototype.h"

void team_created(client_t *client, char **buffer, char *str)
{
    char **new_buffer = my_str_to_word_array(str, ';');

    client_print_team_created(new_buffer[1], new_buffer[2], new_buffer[3]);
}

void team_created_every_user(client_t *client, char **buffer, char *str)
{
    char **new_buffer = my_str_to_word_array(str, ';');

    client_event_team_created(new_buffer[1], new_buffer[2], new_buffer[3]);
}