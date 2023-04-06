/*
** EPITECH PROJECT, 2021
** scub
** File description:
** sub
*/

#include "../include/prototype.h"

void team_subscribed(client_t *client, char **buffer, char *str)
{
    char **new_buffer = my_str_to_word_array(str, ';');

    client_print_subscribed(new_buffer[1], new_buffer[2]);
}
void unknown_team_uuid(client_t *client, char **buffer, char *str)
{
    char **new_buffer = my_str_to_word_array(str, ';');

    client_error_unknown_team(new_buffer[1]);
}

void already_subscribed(client_t *client, char **buffer, char *str)
{
    printf("already subscribed\n");
}

void unsubscribed_to_team(client_t *client, char **buffer, char *str)
{
    char **new_buffer = my_str_to_word_array(str, ';');

    client_print_unsubscribed(new_buffer[1], new_buffer[2]);
}