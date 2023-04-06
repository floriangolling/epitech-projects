/*
** EPITECH PROJECT, 2021
** login
** File description:
** login
*/

#include "../include/prototype.h"

void help(client_t *client, char **buffer, char *str)
{
    for (int i = 0; buffer[i]; i++) {
        printf("%s ", buffer[i]);
    }
    printf("!\n");
}

void login(client_t *client, char **buffer, char *str)
{
    client_event_logged_in(buffer[2], buffer[1]);
    client->is_logged = LOGIN;
    client->uuid = strdup(buffer[2]);
    client->user_name = strdup(buffer[1]);
}

void other_login(client_t *client, char **buffer, char *str)
{
    client_event_logged_in(buffer[2], buffer[1]);
}

void logout(client_t *client, char **buffer, char *str)
{
    if (client->is_logged == LOGIN) {
        client_event_logged_out(buffer[2], buffer[1]);
        client->is_logged = LOGOUT_BUTKNOWN;
        close (client->socket);
        client->socket = -1;
    }
}

void unauthorized(client_t *client, char **buffer, char *str)
{
    client_error_unauthorized();
}