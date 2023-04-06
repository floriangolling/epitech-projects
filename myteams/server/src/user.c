/*
** EPITECH PROJECT, 2021
** userfct
** File description:
** userfct
*/

#include "../include/prototype.h"

int check_if_atleast_login(server_t *srv, char *uuid)
{
    int i = 0;

    for (user_t *tmp = srv->user_list; tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, uuid) == 0 && tmp->is_logged == LOGIN)
            i = 1;
    }
    return (i);
}

void send_user_only(user_t *user, user_t *second_user, server_t *srv,
                                                                char **buff)
{
    int is_logged = check_if_atleast_login(srv, second_user->uuid);

    if (is_logged == 1) {
        dprintf(user->socket, "226 %s %s 1\n", second_user->uuid,
                                                    second_user->user_name);
    } else {
        dprintf(user->socket, "226 %s %s 0\n",second_user->uuid,
                                                    second_user->user_name);
    }
    return;
}

void user_fct(int fd, server_t *srv, char **buff)
{
    user_t *user = find_user_by_fd(fd, srv);
    user_t *second_user = NULL;

    if (buff[1] == NULL)
        return (not_enough_arguments(fd));
    second_user = find_user_by_uuid(buff[1], srv);
    if (!user || user->is_logged != LOGIN)
        return (unauthorized(fd));
    if (!second_user)
        return (send_unknown_uuid(fd, buff[1]));
    send_user_only(user, second_user, srv, buff);
}