/*
** EPITECH PROJECT, 2021
** logout
** File description:
** logout
*/

#include "../include/prototype.h"

void unauthorized(int fd)
{
    dprintf(fd, "504 Unauthorized\n");
    return;
}

void send_user_logout(int fd, char *user_name, char *uuid, server_t *srv)
{
    dprintf(fd, "221 %s %s\n", user_name, uuid);
    for (user_t *tmp = srv->user_list; tmp; tmp = tmp->next) {
        if (tmp->is_logged == LOGIN && tmp->socket != fd)
            dprintf(tmp->socket, "232 %s %s\n", user_name, uuid);
    }
}

void logout_fct(int fd, server_t *srv, char **buff)
{
    user_t *user = find_user_by_fd(fd, srv);

    if (user->is_logged == LOGIN) {
        user->is_logged = LOGOUT_BUTKNOWN;
        user->socket = -1;
        send_user_logout(fd, user->user_name, user->uuid, srv);
        server_event_user_logged_out(user->uuid);
        close (fd);
        FD_CLR(fd, &(srv->active));
        return;
    } else
        return (unauthorized(fd));
}