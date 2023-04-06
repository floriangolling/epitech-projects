/*
** EPITECH PROJECT, 2021
** logout
** File description:
** logout
*/

#include "../include/prototype.h"

void other_logout(client_t *client, char **buffer, char *str)
{
    client_event_logged_out(buffer[2], buffer[1]);
}