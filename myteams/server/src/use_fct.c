/*
** EPITECH PROJECT, 2021
** use
** File description:
** use
*/

#include "../include/prototype.h"

teams_t *find_team_by_uuid(server_t *srv, char *uuid)
{
    for (teams_t *tmp = srv->team_list; tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return (tmp);
    }
    return (NULL);
}

void next_context(int fd, server_t *srv, char **buff, user_t *user)
{
    if (buff[1] != NULL && buff[2] != NULL && buff[3] == NULL) {
        user->context_one = strdup(buff[1]);
        user->context_two = strdup(buff[2]);
        user->context_three = NULL;   
    } else if (buff[1] != NULL && buff[2] != NULL && buff[3] != NULL) {
        user->context_one = strdup(buff[1]);
        user->context_two = strdup(buff[2]);
        user->context_three = strdup(buff[3]);
    }
    return;
}

void use_fct(int fd, server_t *srv, char **buff)
{
    user_t *user = find_user_by_fd(fd, srv);

    if (user->is_logged != LOGIN)
        return (unauthorized(fd));
    user->is_logged = LOGIN;
    if (buff[1] == NULL) {
        user->context_one = NULL;
        user->context_two = NULL;
        user->context_three = NULL;
    }
    else if (buff[1] != NULL && buff[2] == NULL) {
        user->context_one = strdup(buff[1]);
        user->context_two = NULL;
        user->context_three = NULL;
    }
    else
        next_context(fd, srv, buff, user);
}