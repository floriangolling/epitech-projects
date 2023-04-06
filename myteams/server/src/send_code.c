/*
** EPITECH PROJECT, 2021
** sendcode
** File description:
** sendcode
*/

#include "../include/prototype.h"

void send_code(int fd)
{
    dprintf(fd, "505 Already logged in\n");
}

void send_user(int fd, char *user_name, char *uuid, server_t *srv)
{
    dprintf(fd, "220 %s %s\n", user_name, uuid);
    for (user_t *tmp = srv->user_list; tmp; tmp = tmp->next) {
        if (tmp->is_logged == LOGIN && tmp->socket != fd)
            dprintf(tmp->socket, "231 %s %s\n", user_name, uuid);
    }
}