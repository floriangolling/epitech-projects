/*
** EPITECH PROJECT, 2021
** unknocn
** File description:
** unnonc
*/

#include "../include/prototype.h"

void unknown_thread(client_t *client, char **buffer, char *str)
{
    char **new_buffer = my_str_to_word_array(str, ';');

    client_error_unknown_thread(new_buffer[1]);
}

void unknown_channel(client_t *client, char **buffer, char *str)
{
    char **new_buffer = my_str_to_word_array(str, ';');

    client_error_unknown_channel(new_buffer[1]);
}