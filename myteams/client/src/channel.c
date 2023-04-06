/*
** EPITECH PROJECT, 2021
** thread
** File description:
** thread
*/

#include "../include/prototype.h"

void channel_created(client_t *client, char **buffer, char *str)
{
    char **new_buffer = my_str_to_word_array(str, ';');

    client_event_channel_created(new_buffer[1], new_buffer[2], new_buffer[3]);
}

void channel_created_me(client_t *client, char **buffer, char *str)
{
    char **new_buffer = my_str_to_word_array(str, ';');

    client_print_channel_created(new_buffer[1], new_buffer[2], new_buffer[3]);
}
